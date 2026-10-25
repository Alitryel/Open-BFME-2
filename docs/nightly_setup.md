# Nightly builder and publisher setup (maintainer only)

**Superseded** by GitHub-hosted runners: `.github/workflows/nightly-measure.yml`,
set up as described in `docs/nightly_actions.md`. The nightly no longer depends on
the maintainer's PC. This two-account design stays here for reference until it is
removed. Disable its two scheduled tasks after the first green hosted run.

Do this once in an elevated PowerShell, after reviewing the runner and its full
checker dependency tree. These are instructions, not commands the agent ran.
Use a separate **standard local account**, never the maintainer token, for the
builder. The linked game and compiler are untrusted native programs. Do not put
tokens, SSH keys, Git credential helpers, gh logins or signing keys in that account.

The example uses `C:\N` to keep compiler paths short. Replace the publisher name
and the three installed executable paths below with your actual protected
installations. Install Python, Git, OpenSSH and gh machine-wide under Program
Files/Windows, with no builder write access. Never use executables from a checkout
or the builder's user profile. Keep the publisher's PATH free of builder folders.
Install numpy machine-wide into that Python installation: `-I` disables the user
site, so a publisher-only `pip install --user numpy` is insufficient.
This runner must land after the north-star commit containing
`tools/image_ownership.py` from agent-a0b594d3646db42ad's committed branch; approve
that commit or a descendant, not this worktree's older HEAD.

```powershell
$publisher = "$env:COMPUTERNAME\Jonathan"
$publisherProfile = 'C:\Users\Jonathan' # Explicit publisher path, even in another admin's elevated shell.
$builder = "$env:COMPUTERNAME\BFMENightlyBuilder"
$password = Read-Host 'New builder password' -AsSecureString
New-LocalUser -Name BFMENightlyBuilder -Password $password -Description 'Uncredentialed BFME builds'
Add-LocalGroupMember -Group (Get-LocalGroup -SID 'S-1-5-32-545').Name -Member BFMENightlyBuilder
# Keep only standard Users membership; never Administrators or Backup Operators.
$builderSid = (Get-LocalUser BFMENightlyBuilder).SID.Value
$publisherSid = ([System.Security.Principal.NTAccount]$publisher).Translate([System.Security.Principal.SecurityIdentifier]).Value
$python = 'C:\Program Files\Python313\python.exe'
$git = 'C:\Program Files\Git\cmd\git.exe'
$gh = 'C:\Program Files\GitHub CLI\gh.exe'
$sshkeygen = 'C:\Windows\System32\OpenSSH\ssh-keygen.exe'
New-Item -ItemType Directory -Force C:\N,C:\N\install,C:\N\bs,C:\N\ps,C:\N\handoff,C:\N\secrets,C:\N\repo | Out-Null
icacls C:\N /inheritance:r /grant:r "${publisher}:(OI)(CI)(F)" '*S-1-5-18:(OI)(CI)(F)' '*S-1-5-32-544:(OI)(CI)(F)' "${builder}:(RX)"
icacls C:\N\install /inheritance:r /grant:r "${publisher}:(OI)(CI)(F)" '*S-1-5-18:(OI)(CI)(F)' '*S-1-5-32-544:(OI)(CI)(F)' "${builder}:(OI)(CI)(RX)"
icacls C:\N\bs /inheritance:r /grant:r "${builder}:(OI)(CI)(F)" "${publisher}:(OI)(CI)(RX)" '*S-1-5-18:(OI)(CI)(F)' '*S-1-5-32-544:(OI)(CI)(F)'
icacls C:\N\ps /inheritance:r /grant:r "${publisher}:(OI)(CI)(F)" '*S-1-5-18:(OI)(CI)(F)' '*S-1-5-32-544:(OI)(CI)(F)'
icacls C:\N\secrets /inheritance:r /grant:r "${publisher}:(OI)(CI)(F)" '*S-1-5-18:(OI)(CI)(F)' '*S-1-5-32-544:(OI)(CI)(F)'
icacls C:\N\handoff /inheritance:r /grant:r "${builder}:(OI)(CI)(F)" "${publisher}:(OI)(CI)(RX)" '*S-1-5-18:(OI)(CI)(F)' '*S-1-5-32-544:(OI)(CI)(F)'
# No publisher write ACL on handoff; publisher freezes/validates into ps instead.
# Existing targets make the runtime access probes conclusive. Do not replace
# existing stores: create empty placeholders only where there are none.
New-Item -ItemType Directory -Force "$publisherProfile\.ssh","$publisherProfile\AppData\Roaming\GitHub CLI","$publisherProfile\AppData\Local\Microsoft\Credentials","$publisherProfile\AppData\Roaming\Microsoft\Credentials" | Out-Null
if (-not (Test-Path "$publisherProfile\.git-credentials")) { New-Item -ItemType File "$publisherProfile\.git-credentials" | Out-Null }
icacls $publisherProfile /deny "${builder}:(OI)(CI)(RX)"
```

Explicitly remove any pre-existing broad grants on these new directories (the
example assumes they are new). Verify effective access, ownership and ancestor
delete/rename permissions; `/grant:r` only replaces that principal's grants.
Isolation rests on the default profile ACLs plus the runner's access probes.
An `icacls /deny (OI)(CI)` inheritance rule does not reach children with protected
ACLs, such as hardened `.ssh` files. Inspect those children's effective access
separately; the parent deny alone does not prove their isolation.
The builder must not own `C:\N`, install, ps, secrets, the interpreter or tools.
Do not share a Git common directory with a maintainer checkout. Grant access
to the new empty repository directory first:

```powershell
icacls C:\N\repo /inheritance:r /grant:r "${builder}:(OI)(CI)(F)" "${publisher}:(OI)(CI)(RX)" '*S-1-5-18:(OI)(CI)(F)' '*S-1-5-32-544:(OI)(CI)(F)'
```

Sign in interactively once as BFMENightlyBuilder, with no maintainer credentials,
and run `git clone --recurse-submodules https://github.com/Open-BFME/Open-BFME-2.git C:\N\repo`.
Provision the required retail baselines in this clone through the normal setup.
Sign out before returning to the publisher. Do not use a shared Git config or SSH agent.

The publisher keeps its normal gh login, preferably in its user Credential
Manager. Generate the ownership key **as the publisher**, with the existing
image_ownership SSH signing mechanism. Restrict both key and public pin outside
all builder-writable trees:

```powershell
# Press Enter twice at the passphrase prompts (unattended signing; ACL-protected key).
& $sshkeygen -t ed25519 -f C:\N\secrets\ownership_ed25519
$pub = Get-Content C:\N\secrets\ownership_ed25519.pub
"publisher namespaces=`"bfme2-image-ownership`" $pub" | Set-Content -Encoding ascii C:\N\secrets\allowed_signers
# Copy game.dat from your independently verified baseline into the protected install.
Copy-Item '<verified-clone>\baselines\bfme2\workshop-vanilla-1.06\files\game.dat' C:\N\install\retail.dat
$retailSha = (Get-FileHash C:\N\install\retail.dat -Algorithm SHA256).Hash.ToLowerInvariant()
# Populate protected configuration; no private key or token goes in this JSON.
@{builder_sid=$builderSid; publisher_sid=$publisherSid; publisher_profile=$publisherProfile;
  publisher_state='C:\N\ps'; builder_state='C:\N\bs'; signing_key='C:\N\secrets\ownership_ed25519';
  allowed_signers='C:\N\secrets\allowed_signers'; retail_sha256=$retailSha; python=$python;
  executables=@{git=$git; gh=$gh; 'ssh-keygen'=$sshkeygen};
  repository='Open-BFME/Open-BFME-2'; repository_url='https://github.com/Open-BFME/Open-BFME-2.git';
  bfme1_url='https://github.com/Open-BFME/Open-BFME-1.git'; credential_locations=@()
} | ConvertTo-Json -Depth 4 | Set-Content -Encoding utf8 C:\N\install\security.json
# From a reviewed maintainer clone: fetch/review first, then approve a published SHA.
& $python -I tools\nightly_measure.py --root (Get-Location).Path --install-dir C:\N\install --approve origin/master
```

Approval installs the runner at `install\runner\nightly_measure.py` and the whole
approved tools tree at `install\checkers`, and binds both in `approved.json`.
Schedule only this installed file. Renew approval after reviewing changed tools,
vendor, hooks or the BFME1 pin; never have the builder approve itself. Restrict
publisher-only signing material even though it is never passed to a builder child.

Register these two tasks with password prompts (`/rp *`), `LIMITED` tokens and
machine-wide Python. Enable the Task Scheduler Operational log. Publisher triggers
only after builder task completion, and refuses a missing, stale, tampered or
already published handoff; completion of a failed builder never endorses artifacts.
Use Task Scheduler Settings to select **Do not start a new instance** for both
tasks. There is also a separate OS lock per role; handoff freezing tolerates overlap.

```powershell
wevtutil sl Microsoft-Windows-TaskScheduler/Operational /e:true
$common = '-I C:\N\install\runner\nightly_measure.py --root C:\N\repo --install-dir C:\N\install --handoff-dir C:\N\handoff'
$buildAction = '"' + $python + '" ' + $common + ' --role builder --state-dir C:\N\bs --checkout C:\N\repo\build\nightly_measure_wt --snapshot-dir C:\N\s'
$publishAction = '"' + $python + '" ' + $common + ' --role publisher --state-dir C:\N\ps'
# Provision the builder-owned snapshot directory under the protected C:\N parent:
New-Item -ItemType Directory -Force C:\N\s | Out-Null
icacls C:\N\s /inheritance:r /grant:r "${builder}:(OI)(CI)(F)" '*S-1-5-18:(OI)(CI)(F)' '*S-1-5-32-544:(OI)(CI)(F)'
schtasks /create /tn BFME-Nightly-Builder /sc daily /st 01:00 /ru $builder /rp '*' /rl LIMITED /tr $buildAction
$query = "*[System[EventID=102] and EventData[Data[@Name='TaskName']='\BFME-Nightly-Builder']]"
schtasks /create /tn BFME-Nightly-Publisher /sc onevent /ec Microsoft-Windows-TaskScheduler/Operational /mo $query /ru $publisher /rp '*' /rl LIMITED /tr $publishAction
```

Builder must never read the publisher's `.ssh`, `.git-credentials`, GitHub CLI
`hosts.yml`/directory (`C:\Users\Jonathan\AppData\Roaming\GitHub CLI` in this example), Credential Manager storage in both
AppData Microsoft/Credentials locations, signing key, publisher state, other token
stores, or any shared SSH agent. Add relocated credential stores to
`credential_locations`. Preflight uses the actual Windows SID, attempts directory
listing/file opening, and refuses readable stores, inconclusive/missing locations,
or a writable installation/executable. Keep the probe placeholders; a missing
location is inconclusive and stops the builder. Audit custom
`GH_CONFIG_DIR`, `.config\gh`, Windows Vault, browser profiles, cloud credentials,
network shares and group memberships separately. File probes do **not** prove
Credential Manager API isolation, lack of impersonation rights, or all ACLs;
standard-account separation and a maintainer effective-access audit remain required.

Handoffs contain data copies and SHA-256 inventories, not a builder signature of
trust. Publisher drops all supplied Git metadata, copies to private staging,
replaces tools with pinned code, initializes fresh Git metadata from configured
upstreams, rechecks core/closure/bundle/freshness and ownership bound artifacts,
and signs with the existing ownership checker. It publishes the cycle bundle and
a separate `ownership-<cycle-tag>` release with signed history and ownership receipt.
Both workspace and snapshot tracked files must agree with the fetched commit,
including the pinned BFME1 files. Fresh private indexes and `GIT_ATTR_SOURCE=<commit>`
prevent builder attributes or cached file stats from weakening this check.
Line endings are not compared (`core.autocrlf=true`); the checkers read CSV with
`newline=""` and hash text with CRLF stripped, so a CRLF-only change cannot alter
a figure. Untracked extras in the workspace are tolerated: the publisher replaces
`tools/` with its pinned bundle and the checkers read only fixed paths.
Only the snapshot marker and expected products under `build/match`, `build/link_cycle`,
`build/compiler_profiles` and `build/patch` may be untracked in the snapshot.
The pinned `data_back_rank.py` recomputes both rank reports in-process, using a
fresh cache in the publisher's private run directory, and refuses either mismatch.
Link, image and ownership figures remain **builder-attested**: publication does
not independently re-link them. Both releases say so. Before ownership measurement
the publisher adds `measurement_attestation` (schema 1, basis `builder-attested`,
statement) to its private boot report and mirrors it into the receipt. The existing
signed history row's `report_sha256` binds the entire annotated report; that report
is also an ownership release asset. No image_ownership history columns, signature
format or old rows change, so this is backward-compatible with the north-star branch.
It never commits/pushes through checkout hooks. A publisher validation failure
publishes nothing; a later network failure can leave only the cycle release and
returns degraded. Preserve the private run directory to retry deliberately.

Receipts must be portable: relative object, dependency, inventory and spec paths
inside the copied workspace. Non-portable/external paths are refused, never
rewritten. Keep the same approved inputs/flags; changed command fingerprints or
dependency inventories refuse signing. The whole workspace/snapshot copy is
expensive, and all artifacts are still hostile parser inputs. No live two-account
deployment or real nightly has been validated by the fake tests.

Each builder run refuses all pre-existing `build/` content except its marker, and
any committed `build/` path. After a successful handoff it removes only that
dedicated checkout's generated build directory. Failed leftovers require explicit
maintainer cleanup before another run. The clang cache must contain exactly the
hash-pinned `CLANG23_FILES`; extras or changed bytes cause re-extraction from the
pinned zip. `CCC_OVERRIDE_OPTIONS` is dropped. **`build.py` exposes no environment
or approved flag injection point for `--no-default-config`**; this change does not
claim to pass it. Compiler/native compromise remains confined to the builder account.

Command references: [icacls](https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/icacls),
[schtasks create](https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/schtasks-create).
