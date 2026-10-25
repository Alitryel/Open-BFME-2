# Nightly measurement on GitHub Actions (maintainer only)

The nightly link cycle, boot image and image-ownership measurement run on
GitHub-hosted runners: `.github/workflows/nightly-measure.yml`, stages in
`tools/nightly_measure.py --actions`. This replaces the two-Windows-account setup
on the maintainer's PC (`docs/nightly_setup.md`, superseded, kept until removed).
The link census stays on its self-hosted `bfme2-census` runner
(`.github/workflows/link-census.yml`). Agents never trigger, re-run or approve
this workflow.

## What runs where

Trigger: daily at 05:17 UTC and `workflow_dispatch` (optional `dry_run`), on
`master` of `Open-BFME/Open-BFME-2` only. One run at a time
(`concurrency: nightly-measure`, queued, never cancelled). Every job measures
`github.sha`.

| Job | Runner | Token, secrets | Does | Estimate | Timeout |
|---|---|---|---|---|---|
| `boot` | windows-latest | `contents: read`, none | checkout + BFME 1 submodule, `check_csv`, `link_check.py --fetch-index`, full `build.py`, `boot_image.py link --overlay Code/ --relayout --own-data --out build/boot/nightly --tag relayout`, `image_ownership.py report`, `--actions handoff-boot` | 45–90 min | 180 min |
| `cycle` | windows-latest | `contents: read`, none | `link_cycle.py --snapshot <sha> --build` (cold compile in its own export), `publish_cycle.py validate`, `closure_report.py graph`, `publish_cycle.py bundle --first`, `--actions handoff-cycle` | 1.5–4 h | 330 min |
| `publish` | windows-latest | `contents: write`, environment `nightly-publish` | `--actions validate`, write key, `--actions sign`, delete key (`always()`), `--actions publish`, `--actions history` | 40–80 min | 120 min |

`boot` and `cycle` run in parallel: the boot image overlays `Code/` and reads no
cycle output. No `boot_smoke.py` or `game_smoke.py`: hosted runners have no game
install.

Estimates come from receipts, not from a hosted run of this workflow (none has
run yet):

- Full build: `byte-verification.yml` on windows-latest with `BUILD_POOL=4`, six
  successful runs before 2026-10-25: 18.6–37.4 min end to end.
- Link cycle: two receipts.
  - The committed `reverse/link_cycle/receipt.json` (d093315a52, warm compile):
    compile 64 s, provenance 71 s, analyze 115 s, link 2,558 s, measure 43 s;
    47 min in total.
  - The maintainer host's last local receipt, which compiled cold: compile
    9,765 s, provenance 512 s, analyze 518 s, link 833 s, measure 57 s; 3.1 h in
    total.

  The hosted snapshot always compiles cold (no object store). At the hosted
  build's rate the job takes about 1–1.5 h; at the local cold rate, about 4 h.
- Boot link and ownership: no hosted receipt; estimated at 10–30 min.
- Publish: about 1 GB of artifacts (`build/match` alone is about 330 MB here),
  a snapshot export, two ownership measurements, the rank recompute, and two
  five-minute cooldowns between the three GitHub writes.

A single job would run the build, cycle and boot one after another for 2.5–5.5 h,
which is too close to GitHub's 6-hour limit. If the cycle job nears 330 min,
split its compile from its links. That would hand `build/match` across jobs.

## Trust boundaries

- **Build jobs are untrusted.** They hold no secret and no environment. The
  `GITHUB_TOKEN` is read-only and is not persisted in `.git/config`. Their only
  output is a handoff: an allowlist of data files by place and suffix
  (`handoff_allowed`: objects and dependency records, boot report, image, map,
  link products, the bundle; never `.py`, `.pkl`, compiler binaries or the
  snapshot's tracked tree) and a SHA-256 inventory bound to the commit.
- **The publish job runs only its own code.** It checks out `github.sha` itself.
  Every stage refuses to start unless `HEAD` is the measured commit and
  `tools/`, `.githooks/`, `vendor/` and the BFME 1 pin are unmodified, with no
  untracked or ignored file beside them except bytecode caches. The job runs no build, link, boot or
  game executable. The snapshot's tracked tree is re-exported from this job's
  own git (`link_cycle.export_snapshot`). Only the build products from the
  handoffs are installed, into directories that must be fresh, and the clang
  cache is re-extracted from the pinned zip. The checks run as isolated
  `python -I` children under `publisher_process_guard`, which may start only
  `git`, `gh` and `ssh-keygen`.
- **What it re-validates** (the existing publisher logic: `PUBLISHER_CHECKS`,
  `recompute_rank`, `check_artifact_paths`, `PUBLISHER_OWNERSHIP`):
  - Commit binding of each handoff, the receipt, the bundle manifest and the
    boot provenance.
  - The receipt core, recomputed with this commit's `link_cycle`.
  - The receipt's tree manifest against the publisher's own export.
  - Bundle integrity, receipt freshness and ancestry, and the closure graph.
  - `data_back_rank`, recomputed in-process; it must equal the builder's.
  - Portable artifact paths.
  - The bound ownership measurement: image and map bound to the report, objects
    current for their sources (`record_refusals`).
- **Link, image and ownership figures stay builder-attested.** Nobody re-links
  them. Both releases and the boot report's `measurement_attestation` say so.
  The signed row's `report_sha256` binds the report.
- **Secrets are scoped to steps.**
  - `BFME_OWNERSHIP_SIGNING_KEY` exists only in the step that writes the key
    file (`RUNNER_TEMP\nightly-secrets`, icacls: this account only, the key
    read-only). The file is deleted by `--actions sign` when it ends, and again
    by an `always()` step.
  - `BFME_RELEASE_TOKEN` is passed only to `--actions publish`.
  - `github.token` is used only by `--actions history`, as a per-process
    `extraheader`.
  - Children never inherit the key's variables, and get the release token only
    for `gh` calls.
- **The trust root is `master`.** The local design pinned an approved tools
  tree. Here, whoever can change `.github/workflows/` or `tools/` on `master`
  controls the publish job and the secrets it receives. Such commits need a
  `Verifier-Change` trailer (`tools/protected_paths.py`). The environment's
  protection rules are the only extra lever: required reviewers make the
  maintainer approve each publish.

## How the history row reaches master

`--actions history` pushes the row directly to `master`. Before it commits, it
deletes every downloaded artifact. It then commits through the repository's own
hooks (`git -c core.hooksPath=.githooks commit`; `pre-commit` runs
`image_ownership.py check-history --staged` against the pin), rebases onto the
fetched `master`, and pushes through `pre-push` (up to three times, five
minutes apart). The commit may change only `reverse/image_ownership_history.csv`.

Why this route:

- A commit made in Actions skips hooks only if nobody enables them. This one
  enables them, so the row passes the same gate an agent's commit passes, with
  no `--no-verify`.
- `AGENTS.md` forbids the merge button because a merge publishes rows nothing
  verified. A pull request would need that button, or a human cherry-pick every
  night.
- The row is verified twice before the push: `record()` re-hashes the bound
  image, map and objects under its lock, and `check_history` verifies the
  signature against the pin.
- `readme-progress.yml` already pushes its daily data commit as
  `github-actions[bot]` in the same way.
- If every push fails (a lost race, a hook refusal or a ruleset), the job fails.
  The signed row and receipt stay in the ownership release and the logs
  artifact. Re-record on the new tip; never hand-edit the row.

## Maintainer setup

1. **Immutable releases**: Settings > General > Releases > enable. Without it,
   `publish_cycle.py publish` refuses.
2. **Environment** `nightly-publish` (Settings > Environments). Set deployment
   branches and tags to `master` only. Optionally add yourself as a required
   reviewer.
3. **Signing key**, generated offline:
   `ssh-keygen -t ed25519 -N "" -C bfme2-nightly -f ownership_ed25519`.
   - Environment secret `BFME_OWNERSHIP_SIGNING_KEY`: the whole private key file.
   - Environment variable `BFME_OWNERSHIP_ALLOWED_SIGNERS`: the one-line pin,
     `publisher namespaces="bfme2-image-ownership" ssh-ed25519 AAAA...`, from
     `ownership_ed25519.pub`.
   - Keep the pin the same everywhere the hooks verify rows: seats that commit
     the history file set `BFME_OWNERSHIP_ALLOWED_SIGNERS` to a copy outside
     the repository.
4. **Release token**: environment secret `BFME_RELEASE_TOKEN`, a fine-grained
   personal access token.
   - Repository access: only `Open-BFME/Open-BFME-2`.
   - Permissions: Contents read/write, Administration read-only (for
     `GET /repos/{repo}/immutable-releases`), Metadata read.
   - Its account must be listed in `cycle_artifacts.PUBLISHERS` (login and
     numeric id; today `Ancalgonn`, 1760627). Consumers refuse a release by
     anyone else.
   - A dedicated bot account limits what a leaked token can do. Adding one
     means a reviewed `tools/cycle_artifacts.py` change with a
     `Verifier-Change` trailer.
   - The workflow does not use `GITHUB_TOKEN` for releases. That token cannot
     read `GET /user` or the immutable-release setting. Also, any workflow with
     `contents: write` on any branch could author a `github-actions[bot]`
     release.
5. **Push to master**: the history push is made as `github-actions[bot]` with
   the job's `GITHUB_TOKEN`. If a branch ruleset blocks it, allow GitHub Actions
   to bypass it for this push, or accept that the row stays in the release.
6. **Retire the local tasks** after the first green hosted run: disable
   `BFME-Nightly-Builder` and `BFME-Nightly-Publisher` in Task Scheduler.

## First manual run

1. Run a dry run: Actions > Nightly measurement > Run workflow, branch
   `master`, `dry_run` checked. Or from the command line:
   `gh workflow run nightly-measure.yml --ref master -f dry_run=true`.
   A dry run builds, links, validates and re-measures ownership.
   `publish_cycle.py publish --dry-run` checks the token, `PUBLISHERS` and the
   immutable-release setting. Nothing is recorded, released or pushed.
2. Read the `nightly-publish-logs-<attempt>` artifact:
   - `logs/handoff-validate.log`: the core must be "recomputed with
     link_cycle".
   - `logs/rank.log`
   - `logs/ownership-measure.log`
   - `logs/publish.log`: the dry run's warnings.
3. Run it without `dry_run`, or wait for the schedule. Check:
   - the `link-cycle/...` prerelease (immutable, authored by the token's
     account);
   - the `ownership-link-cycle-...` prerelease;
   - the `image_ownership: nightly measurement at <sha>` commit on `master`.
