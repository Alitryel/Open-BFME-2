// DXGetErrorDescription9A, retail 0x0064E91A, whole 11,497-byte stdcall body.
// Identity, ABI and boundary: original August 2005 DirectX SDK dxerr9.lib,
// member obj\i386\dxerr9.obj; same exported name and complete retail body.
// Microsoft DXUT 2c3ad3ceaf99a7aaff5278dabc2cc952c727d8c1 Core/dxerr.cpp
// (Copyright Microsoft Corporation; MIT License, see license.dxut.txt) supplies
// the semantic switch/return structure only. Every HRESULT and exact literal
// below is independently recovered from the complete bounded retail CFG.
// Original COFF line records prove ordering and case grouping: every recovered
// return offset has an exact original line entry. Macro spellings are unknown.
// 656 non-default HRESULT cases, 625 original source groups;
// default is 'n/a'. Full instruction, jump-table and literal gates
// are required together; matching relocation-masked bytes alone is insufficient.
// Compiler 13.10.4035 is recorded in the original archive CodeView. The
// authenticated Microsoft DDK profile reproduces the complete native body.
// compiler: vc71-ddk-4035
// cl: /O1 /G6 /MT /DNDEBUG /hotpatch /Oy- /GS
// Case groups follow the original object COFF line records.
extern "C" const char * __stdcall DXGetErrorDescription9A(long hr)
{
    switch (hr)
    {
    // Original object relative source line 6.
    case 0x00000000: return "The function completed successfully";
    // Original object relative source line 7.
    case 0x00000001: return "Call successful, but returned FALSE";
    // Original object relative source line 9.
    case 0x8000FFFF: return "Catastrophic failure";
    // Original object relative source line 10.
    case 0x80004001: return "The function called is not supported at this time";
    // Original object relative source line 11.
    case 0x8007000E: return "Ran out of memory";
    // Original object relative source line 12.
    case 0x80070057: return "An invalid parameter was passed to the returning function";
    // Original object relative source line 13.
    case 0x80004002: return "The requested COM interface is not available";
    // Original object relative source line 14.
    case 0x80004003: return "Invalid pointer";
    // Original object relative source line 16.
    case 0x80004004: return "Operation aborted";
    // Original object relative source line 17.
    case 0x80004005: return "An undetermined error occurred";
    // Original object relative source line 18.
    case 0x80070005: return "Access is denied";
    // Original object relative source line 19.
    case 0x8000000A: return "The data necessary to complete this operation is not yet available.";
    // Original object relative source line 20.
    case 0x80040154: return "Class not registered";
    // Original object relative source line 21.
    case 0x800401F0: return "CoInitialize has not been called.";
    // Original object relative source line 22.
    case 0x800401F1: return "CoInitialize has already been called.";
    // Original object relative source line 23.
    case 0x80040110: return "This object does not support aggregation";
    // Original object relative source line 25.
    case 0x00000002:
    case 0x80070002: return "The system cannot find the file specified.";
    // Original object relative source line 26.
    case 0x00000003:
    case 0x80070003: return "The system cannot find the path specified.";
    // Original object relative source line 27.
    case 0x00000004:
    case 0x80070004: return "The system cannot open the file.";
    // Original object relative source line 28.
    case 0x00000005: return "Access is denied.";
    // Original object relative source line 29.
    case 0x00000006: return "The handle is invalid.";
    // Original object relative source line 30.
    case 0x00000008:
    case 0x80070008: return "Not enough storage is available to process this command.";
    // Original object relative source line 31.
    case 0x00000009:
    case 0x80070009: return "The storage control block address is invalid.";
    // Original object relative source line 32.
    case 0x0000000A:
    case 0x8007000A: return "The environment is incorrect.";
    // Original object relative source line 33.
    case 0x0000000B:
    case 0x8007000B: return "An attempt was made to load a program with an incorrect format.";
    // Original object relative source line 34.
    case 0x0000000E: return "The system cannot find the drive specified.";
    // Original object relative source line 41.
    case 0x8876000A: return "This surface can not be attached to the requested surface.";
    // Original object relative source line 42.
    case 0x88760014: return "This surface can not be detached from the requested surface.";
    // Original object relative source line 43.
    case 0x88760028: return "Support is currently not available.";
    // Original object relative source line 44.
    case 0x88760037: return "An exception was encountered while performing the requested operation";
    // Original object relative source line 46.
    case 0x8876005A: return "Height of rectangle provided is not a multiple of reqd alignment";
    // Original object relative source line 47.
    case 0x8876005F: return "Unable to match primary surface creation request with existing primary surface.";
    // Original object relative source line 48.
    case 0x88760064: return "One or more of the caps bits passed to the callback are incorrect.";
    // Original object relative source line 49.
    case 0x8876006E: return "DirectDraw does not support provided Cliplist.";
    // Original object relative source line 50.
    case 0x88760078: return "DirectDraw does not support the requested mode";
    // Original object relative source line 51.
    case 0x88760082: return "DirectDraw received a pointer that was an invalid DIRECTDRAW object.";
    // Original object relative source line 53.
    case 0x88760091: return "pixel format was invalid as specified";
    // Original object relative source line 54.
    case 0x88760096: return "Rectangle provided was invalid.";
    // Original object relative source line 55.
    case 0x887600A0: return "Operation could not be carried out because one or more surfaces are locked";
    // Original object relative source line 56.
    case 0x887600AA: return "There is no 3D present.";
    // Original object relative source line 57.
    case 0x887600B4: return "Operation could not be carried out because there is no alpha accleration hardware present or available.";
    // Original object relative source line 58.
    case 0x887600B5: return "Operation could not be carried out because there is no stereo hardware present or available.";
    // Original object relative source line 59.
    case 0x887600B6: return "Operation could not be carried out because there is no hardware present which supports stereo surfaces";
    // Original object relative source line 60.
    case 0x887600CD: return "no clip list available";
    // Original object relative source line 61.
    case 0x887600D2: return "Operation could not be carried out because there is no color conversion hardware present or available.";
    // Original object relative source line 62.
    case 0x887600D4: return "Create function called without DirectDraw object method SetCooperativeLevel being called.";
    // Original object relative source line 63.
    case 0x887600D7: return "Surface doesn't currently have a color key";
    // Original object relative source line 64.
    case 0x887600DC: return "Operation could not be carried out because there is no hardware support of the dest color key.";
    // Original object relative source line 65.
    case 0x887600DE: return "No DirectDraw support possible with current display driver";
    // Original object relative source line 66.
    case 0x887600E1: return "Operation requires the application to have exclusive mode but the application does not have exclusive mode.";
    // Original object relative source line 67.
    case 0x887600E6: return "Flipping visible surfaces is not supported.";
    // Original object relative source line 68.
    case 0x887600F0: return "There is no GDI present.";
    // Original object relative source line 69.
    case 0x887600FA: return "Operation could not be carried out because there is no hardware present or available.";
    // Original object relative source line 70.
    case 0x887600FF: return "Requested item was not found";
    // Original object relative source line 71.
    case 0x88760104: return "Operation could not be carried out because there is no overlay hardware present or available.";
    // Original object relative source line 72.
    case 0x8876010E: return "Operation could not be carried out because the source and destination rectangles are on the same surface and overlap each other.";
    // Original object relative source line 73.
    case 0x88760118: return "Operation could not be carried out because there is no appropriate raster op hardware present or available.";
    // Original object relative source line 74.
    case 0x88760122: return "Operation could not be carried out because there is no rotation hardware present or available.";
    // Original object relative source line 75.
    case 0x88760136: return "Operation could not be carried out because there is no hardware support for stretching";
    // Original object relative source line 76.
    case 0x8876013C: return "DirectDrawSurface is not in 4 bit color palette and the requested operation requires 4 bit color palette.";
    // Original object relative source line 77.
    case 0x8876013D: return "DirectDrawSurface is not in 4 bit color index palette and the requested operation requires 4 bit color index palette.";
    // Original object relative source line 78.
    case 0x88760140: return "DirectDraw Surface is not in 8 bit color mode and the requested operation requires 8 bit color.";
    // Original object relative source line 79.
    case 0x8876014A: return "Operation could not be carried out because there is no texture mapping hardware present or available.";
    // Original object relative source line 80.
    case 0x8876014F: return "Operation could not be carried out because there is no hardware support for vertical blank synchronized operations.";
    // Original object relative source line 81.
    case 0x88760154: return "Operation could not be carried out because there is no hardware support for zbuffer blting.";
    // Original object relative source line 82.
    case 0x8876015E: return "Overlay surfaces could not be z layered based on their BltOrder because the hardware does not support z layering of overlays.";
    // Original object relative source line 83.
    case 0x88760168: return "The hardware needed for the requested operation has already been allocated.";
    // Original object relative source line 86.
    case 0x8876017E: return "hardware does not support clipped overlays";
    // Original object relative source line 87.
    case 0x88760180: return "Can only have ony color key active at one time for overlays";
    // Original object relative source line 88.
    case 0x88760183: return "Access to this palette is being refused because the palette is already locked by another thread.";
    // Original object relative source line 89.
    case 0x88760190: return "No src color key specified for this operation.";
    // Original object relative source line 90.
    case 0x8876019A: return "This surface is already attached to the surface it is being attached to.";
    // Original object relative source line 91.
    case 0x887601A4: return "This surface is already a dependency of the surface it is being made a dependency of.";
    // Original object relative source line 92.
    case 0x887601AE: return "Access to this surface is being refused because the surface is already locked by another thread.";
    // Original object relative source line 93.
    case 0x887601B3: return "Access to this surface is being refused because no driver exists which can supply a pointer to the surface. This is most likely to happen when attempting to lock the primary surface when no DCI provider is present. Will also happen on attempts to lock an optimized surface.";
    // Original object relative source line 94.
    case 0x887601B8: return "Access to Surface refused because Surface is obscured.";
    // Original object relative source line 95.
    case 0x887601C2: return "Access to this surface is being refused because the surface is gone. The DIRECTDRAWSURFACE object representing this surface should have Restore called on it.";
    // Original object relative source line 96.
    case 0x887601CC: return "The requested surface is not attached.";
    // Original object relative source line 97.
    case 0x887601D6: return "Height requested by DirectDraw is too large.";
    // Original object relative source line 98.
    case 0x887601E0: return "Size requested by DirectDraw is too large --  The individual height and width are OK.";
    // Original object relative source line 99.
    case 0x887601EA: return "Width requested by DirectDraw is too large.";
    // Original object relative source line 101.
    case 0x887601FE: return "Pixel format requested is unsupported by DirectDraw";
    // Original object relative source line 102.
    case 0x88760208: return "Bitmask in the pixel format requested is unsupported by DirectDraw";
    // Original object relative source line 103.
    case 0x88760209: return "The specified stream contains invalid data";
    // Original object relative source line 104.
    case 0x88760219: return "vertical blank is in progress";
    // Original object relative source line 105.
    case 0x8876021C: return "Was still drawing";
    // Original object relative source line 106.
    case 0x8876021E: return "The specified surface type requires specification of the COMPLEX flag";
    // Original object relative source line 107.
    case 0x88760230: return "Rectangle provided was not horizontally aligned on reqd. boundary";
    // Original object relative source line 108.
    case 0x88760231: return "The GUID passed to DirectDrawCreate is not a valid DirectDraw driver identifier.";
    // Original object relative source line 109.
    case 0x88760232: return "A DirectDraw object representing this driver has already been created for this process.";
    // Original object relative source line 110.
    case 0x88760233: return "A hardware only DirectDraw object creation was attempted but the driver did not support any hardware.";
    // Original object relative source line 111.
    case 0x88760234: return "this process already has created a primary surface";
    // Original object relative source line 112.
    case 0x88760235: return "software emulation not available.";
    // Original object relative source line 113.
    case 0x88760236: return "region passed to Clipper::GetClipList is too small.";
    // Original object relative source line 114.
    case 0x88760237: return "an attempt was made to set a clip list for a clipper objec that is already monitoring an hwnd.";
    // Original object relative source line 115.
    case 0x88760238: return "No clipper object attached to surface object";
    // Original object relative source line 116.
    case 0x88760239: return "Clipper notification requires an HWND or no HWND has previously been set as the CooperativeLevel HWND.";
    // Original object relative source line 117.
    case 0x8876023A: return "HWND used by DirectDraw CooperativeLevel has been subclassed, this prevents DirectDraw from restoring state.";
    // Original object relative source line 118.
    case 0x8876023B: return "The CooperativeLevel HWND has already been set. It can not be reset while the process has surfaces or palettes created.";
    // Original object relative source line 119.
    case 0x8876023C: return "No palette object attached to this surface.";
    // Original object relative source line 120.
    case 0x8876023D: return "No hardware support for 16 or 256 color palettes.";
    // Original object relative source line 121.
    case 0x8876023E: return "If a clipper object is attached to the source surface passed into a BltFast call.";
    // Original object relative source line 122.
    case 0x8876023F: return "No blter.";
    // Original object relative source line 123.
    case 0x88760240: return "No DirectDraw ROP hardware.";
    // Original object relative source line 124.
    case 0x88760241: return "returned when GetOverlayPosition is called on a hidden overlay";
    // Original object relative source line 125.
    case 0x88760242: return "returned when GetOverlayPosition is called on a overlay that UpdateOverlay has never been called on to establish a destionation.";
    // Original object relative source line 126.
    case 0x88760243: return "returned when the position of the overlay on the destionation is no longer legal for that destionation.";
    // Original object relative source line 127.
    case 0x88760244: return "returned when an overlay member is called for a non-overlay surface";
    // Original object relative source line 128.
    case 0x88760245: return "An attempt was made to set the cooperative level when it was already set to exclusive.";
    // Original object relative source line 129.
    case 0x88760246: return "An attempt has been made to flip a surface that is not flippable.";
    // Original object relative source line 130.
    case 0x88760247: return "Can't duplicate primary & 3D surfaces, or surfaces that are implicitly created.";
    // Original object relative source line 131.
    case 0x88760248: return "Surface was not locked.  An attempt to unlock a surface that was not locked at all, or by this process, has been attempted.";
    // Original object relative source line 132.
    case 0x88760249: return "Windows can not create any more DCs, or a DC was requested for a paltte-indexed surface when the surface had no palette AND the display mode was not palette-indexed (in this case DirectDraw cannot select a proper palette into the DC)";
    // Original object relative source line 133.
    case 0x8876024A: return "No DC was ever created for this surface.";
    // Original object relative source line 134.
    case 0x8876024B: return "This surface can not be restored because it was created in a different mode.";
    // Original object relative source line 135.
    case 0x8876024C: return "This surface can not be restored because it is an implicitly created surface.";
    // Original object relative source line 136.
    case 0x8876024D: return "The surface being used is not a palette-based surface";
    // Original object relative source line 137.
    case 0x8876024E: return "The display is currently in an unsupported mode";
    // Original object relative source line 138.
    case 0x8876024F: return "Operation could not be carried out because there is no mip-map texture mapping hardware present or available.";
    // Original object relative source line 139.
    case 0x88760250: return "The requested action could not be performed because the surface was of the wrong type.";
    // Original object relative source line 140.
    case 0x88760258: return "Device does not support optimized surfaces, therefore no video memory optimized surfaces";
    // Original object relative source line 141.
    case 0x88760259: return "Surface is an optimized surface, but has not yet been allocated any memory";
    // Original object relative source line 142.
    case 0x8876025A: return "Attempt was made to create or set a device window without first setting the focus window";
    // Original object relative source line 143.
    case 0x8876025B: return "Attempt was made to set a palette on a mipmap sublevel";
    // Original object relative source line 144.
    case 0x8876026C: return "A DC has already been returned for this surface. Only one DC can be retrieved per surface.";
    // Original object relative source line 145.
    case 0x88760276: return "An attempt was made to allocate non-local video memory from a device that does not support non-local video memory.";
    // Original object relative source line 146.
    case 0x88760280: return "The attempt to page lock a surface failed.";
    // Original object relative source line 147.
    case 0x88760294: return "The attempt to page unlock a surface failed.";
    // Original object relative source line 148.
    case 0x887602A8: return "An attempt was made to page unlock a surface with no outstanding page locks.";
    // Original object relative source line 149.
    case 0x887602B2: return "There is more data available than the specified buffer size could hold";
    // Original object relative source line 150.
    case 0x887602B3: return "The data has expired and is therefore no longer valid.";
    // Original object relative source line 151.
    case 0x887602B4: return "The mode test has finished executing.";
    // Original object relative source line 152.
    case 0x887602B5: return "The mode test has switched to a new mode.";
    // Original object relative source line 153.
    case 0x887602B6: return "D3D has not yet been initialized.";
    // Original object relative source line 154.
    case 0x887602B7: return "The video port is not active";
    // Original object relative source line 155.
    case 0x887602B8: return "The monitor does not have EDID data.";
    // Original object relative source line 156.
    case 0x887602B9: return "The driver does not enumerate display mode refresh rates.";
    // Original object relative source line 157.
    case 0x887602BB: return "Surfaces created by one direct draw device cannot be used directly by another direct draw device.";
    // Original object relative source line 175.
    case 0x8007047E: return "The application requires a newer version of DirectInput.";
    // Original object relative source line 178.
    case 0x80070481: return "The application was written for an unsupported prerelease version of DirectInput.";
    // Original object relative source line 179.
    case 0x80070077: return "The object could not be created due to an incompatible driver version or mismatched or incomplete driver components.";
    // Original object relative source line 192.
    case 0x8007001E: return "Access to the device has been lost.  It must be re-acquired.";
    // Original object relative source line 193.
    case 0x800700AA: return "The operation cannot be performed while the device is acquired.";
    // Original object relative source line 194.
    case 0x8007000C: return "The operation cannot be performed unless the device is acquired.";
    // Original object relative source line 197.
    case 0x80040200: return "Unable to IDirectInputJoyConfig_Acquire because the user does not have sufficient privileges to change the joystick configuration. & An invalid media type was specified";
    // Original object relative source line 198.
    case 0x80040201: return "The device is full. & An invalid media subtype was specified.";
    // Original object relative source line 199.
    case 0x80040202: return "Not all the requested information fit into the buffer. & This object can only be created as an aggregated object.";
    // Original object relative source line 200.
    case 0x80040203: return "The effect is not downloaded. & The enumerator has become invalid.";
    // Original object relative source line 201.
    case 0x80040204: return "The device cannot be reinitialized because there are still effects attached to it. & At least one of the pins involved in the operation is already connected.";
    // Original object relative source line 202.
    case 0x80040205: return "The operation cannot be performed unless the device is acquired in DISCL_EXCLUSIVE mode. & This operation cannot be performed because the filter is active.";
    // Original object relative source line 203.
    case 0x80040206: return "The effect could not be downloaded because essential information is missing.  For example, no axes have been associated with the effect, or no type-specific information has been created. & One of the specified pins supports no media types.";
    // Original object relative source line 204.
    case 0x80040207: return "Attempted to read buffered device data from a device that is not buffered. & There is no common media type between these pins.";
    // Original object relative source line 205.
    case 0x80040208: return "An attempt was made to modify parameters of an effect while it is playing.  Not all hardware devices support altering the parameters of an effect while it is playing. & Two pins of the same direction cannot be connected together.";
    // Original object relative source line 206.
    case 0x80040209: return "The operation could not be completed because the device is not plugged in. & The operation cannot be performed because the pins are not connected.";
    // Original object relative source line 207.
    case 0x8004020A: return "SendDeviceData failed because more information was requested to be sent than can be sent to the device.  Some devices have restrictions on how much data can be sent to them.  (For example, there might be a limit on the number of buttons that can be pressed at once.) & No sample buffer allocator is available.";
    // Original object relative source line 208.
    case 0x8004020B: return "A mapper file function failed because reading or writing the user or IHV settings file failed. & A run-time error occurred.";
    // Original object relative source line 214.
    case 0x80070103: return "No more items.";
    // Original object relative source line 215.
    case 0x80040300: return "Device driver-specific codes. Unless the specific driver has been precisely identified, no meaning should be attributed to these values other than that the driver originated the error.";
    // Original object relative source line 216.
    case 0x80040301: return "DIERR_DRIVERFIRST+1";
    // Original object relative source line 217.
    case 0x80040302: return "DIERR_DRIVERFIRST+2";
    // Original object relative source line 218.
    case 0x80040303: return "DIERR_DRIVERFIRST+3";
    // Original object relative source line 219.
    case 0x80040304: return "DIERR_DRIVERFIRST+4";
    // Original object relative source line 220.
    case 0x80040305: return "DIERR_DRIVERFIRST+5";
    // Original object relative source line 221.
    case 0x800403FF: return "Device installer errors.";
    // Original object relative source line 222.
    case 0x80040400: return "Registry entry or DLL for class installer invalid or class installer not found.";
    // Original object relative source line 223.
    case 0x80040401: return "The user cancelled the install operation. & The stream already has allocated samples and the surface doesn't match the sample format.";
    // Original object relative source line 224.
    case 0x80040402: return "The INF file for the selected device could not be found or is invalid or is damaged. & The specified purpose ID can't be used for the call.";
    // Original object relative source line 231.
    case 0x00150005: return "Full duplex";
    // Original object relative source line 232.
    case 0x0015000A: return "Half duplex";
    // Original object relative source line 233.
    case 0x00150010: return "Pending";
    // Original object relative source line 246.
    case 0x8015012C: return "Session lost";
    // Original object relative source line 247.
    case 0x8015012E: return "No voice session";
    // Original object relative source line 249.
    case 0x80150169: return "Not initialized";
    // Original object relative source line 250.
    case 0x8015016A: return "Connected";
    // Original object relative source line 251.
    case 0x8015016B: return "Not connected";
    // Original object relative source line 252.
    case 0x8015016E: return "Connect aborting";
    // Original object relative source line 254.
    case 0x80150170: return "Invalid target";
    // Original object relative source line 255.
    case 0x80150171: return "Transport not host";
    // Original object relative source line 256.
    case 0x80150172: return "Compression not supported";
    // Original object relative source line 257.
    case 0x80150173: return "Already pending";
    // Original object relative source line 258.
    case 0x80150174: return "Sound init failure";
    // Original object relative source line 259.
    case 0x80150175: return "Time out";
    // Original object relative source line 260.
    case 0x80150176: return "Connect aborted";
    // Original object relative source line 261.
    case 0x80150177: return "No 3d sound";
    // Original object relative source line 262.
    case 0x80150178: return "Already buffered";
    // Original object relative source line 263.
    case 0x80150179: return "Not buffered";
    // Original object relative source line 265.
    case 0x8015017B: return "Not hosting";
    // Original object relative source line 267.
    case 0x8015017D: return "Record system error";
    // Original object relative source line 268.
    case 0x8015017E: return "Playback system error";
    // Original object relative source line 269.
    case 0x8015017F: return "Send error";
    // Original object relative source line 271.
    case 0x80150183: return "Run setup";
    // Original object relative source line 272.
    case 0x80150184: return "Incompatible version";
    // Original object relative source line 273.
    case 0x80150187: return "Initialized";
    // Original object relative source line 275.
    case 0x80150188: return "No transport";
    // Original object relative source line 276.
    case 0x80150189: return "No callback";
    // Original object relative source line 277.
    case 0x8015018A: return "Transport not init";
    // Original object relative source line 278.
    case 0x8015018B: return "Transport no session";
    // Original object relative source line 279.
    case 0x8015018C: return "Transport no player";
    // Original object relative source line 280.
    case 0x8015018D: return "User back";
    // Original object relative source line 281.
    case 0x8015018E: return "No rec vol available";
    // Original object relative source line 282.
    case 0x8015018F: return "Invalid buffer";
    // Original object relative source line 283.
    case 0x80150190: return "Locked buffer";
    // Original object relative source line 289.
    case 0x80158030: return "Aborted";
    // Original object relative source line 290.
    case 0x80158040: return "Addressing";
    // Original object relative source line 291.
    case 0x80158050: return "Already closing";
    // Original object relative source line 292.
    case 0x80158060: return "Already connected";
    // Original object relative source line 293.
    case 0x80158070: return "Already disconnecting";
    // Original object relative source line 294.
    case 0x80158080: return "Already initialized";
    // Original object relative source line 295.
    case 0x80158090: return "Already registered";
    // Original object relative source line 296.
    case 0x8015001E:
    case 0x80158100: return "Buffer too small";
    // Original object relative source line 297.
    case 0x80158110: return "Can not cancel";
    // Original object relative source line 298.
    case 0x80158120: return "Cant create group";
    // Original object relative source line 299.
    case 0x80158130: return "Cant create player";
    // Original object relative source line 300.
    case 0x80158140: return "Cant launch application";
    // Original object relative source line 301.
    case 0x80158150: return "Connecting";
    // Original object relative source line 302.
    case 0x80150168:
    case 0x80158160: return "Connection lost";
    // Original object relative source line 303.
    case 0x80158170: return "Conversion";
    // Original object relative source line 304.
    case 0x80158175: return "Data too large";
    // Original object relative source line 305.
    case 0x80158180: return "Does not exist";
    // Original object relative source line 306.
    case 0x80158185: return "dpnsvr not available";
    // Original object relative source line 307.
    case 0x80158190: return "Duplicate command";
    // Original object relative source line 308.
    case 0x80158200: return "End point not receiving";
    // Original object relative source line 309.
    case 0x80158210: return "Enum query too large";
    // Original object relative source line 310.
    case 0x80158220: return "Enum response too large";
    // Original object relative source line 311.
    case 0x8015004A:
    case 0x80158230: return "Exception";
    // Original object relative source line 312.
    case 0x80158240: return "Group not empty";
    // Original object relative source line 313.
    case 0x8015017A:
    case 0x80158250: return "Hosting";
    // Original object relative source line 314.
    case 0x80158260: return "Host rejected connection";
    // Original object relative source line 315.
    case 0x80158270: return "Host terminated session";
    // Original object relative source line 316.
    case 0x80158280: return "Incomplete address";
    // Original object relative source line 317.
    case 0x80158290: return "Invalid address format";
    // Original object relative source line 318.
    case 0x80158300: return "Invalid application";
    // Original object relative source line 319.
    case 0x80158310: return "Invalid command";
    // Original object relative source line 320.
    case 0x80158330: return "Invalid end point";
    // Original object relative source line 321.
    case 0x80150078:
    case 0x80158340: return "Invalid flags";
    // Original object relative source line 322.
    case 0x80150091:
    case 0x80158350: return "Invalid group";
    // Original object relative source line 323.
    case 0x80070006:
    case 0x80150096:
    case 0x80158360: return "Invalid handle";
    // Original object relative source line 324.
    case 0x80158380: return "Invalid instance";
    // Original object relative source line 325.
    case 0x80158390: return "Invalid interface";
    // Original object relative source line 326.
    case 0x80158320: return "Invalid device address";
    // Original object relative source line 327.
    case 0x80150082:
    case 0x80158400: return "Invalid object";
    // Original object relative source line 329.
    case 0x80158410: return "Invalid password";
    // Original object relative source line 330.
    case 0x80150087:
    case 0x80158420: return "Invalid player";
    // Original object relative source line 332.
    case 0x80158430: return "Invalid priority";
    // Original object relative source line 333.
    case 0x80158370: return "Invalid host address";
    // Original object relative source line 334.
    case 0x80158440: return "Invalid string";
    // Original object relative source line 335.
    case 0x80158450: return "Invalid url";
    // Original object relative source line 336.
    case 0x80158460: return "Invalid version";
    // Original object relative source line 337.
    case 0x80158470: return "No caps";
    // Original object relative source line 338.
    case 0x80158480: return "No connection";
    // Original object relative source line 339.
    case 0x80158490: return "No host player";
    // Original object relative source line 341.
    case 0x80158500: return "No more address components";
    // Original object relative source line 342.
    case 0x80158510: return "No response";
    // Original object relative source line 343.
    case 0x8015016F:
    case 0x80158520: return "Not allowed";
    // Original object relative source line 344.
    case 0x80158530: return "Not host";
    // Original object relative source line 345.
    case 0x80158540: return "Not ready";
    // Original object relative source line 346.
    case 0x80158550: return "Not registered";
    // Original object relative source line 349.
    case 0x80158560: return "Player already in group";
    // Original object relative source line 350.
    case 0x80158570: return "Player lost";
    // Original object relative source line 351.
    case 0x80158580: return "Player not in group";
    // Original object relative source line 352.
    case 0x80158590: return "Player not reachable";
    // Original object relative source line 353.
    case 0x80158600: return "Send too large";
    // Original object relative source line 354.
    case 0x80158610: return "Session full";
    // Original object relative source line 355.
    case 0x80158620: return "Table full";
    // Original object relative source line 356.
    case 0x80158630: return "Timed out";
    // Original object relative source line 357.
    case 0x80158640: return "Uninitialized";
    // Original object relative source line 359.
    case 0x80150180:
    case 0x80158650: return "User cancel";
    // Original object relative source line 389.
    case 0x88760366: return "Internal error";
    // Original object relative source line 391.
    case 0x88760368: return "Bad intrinsics";
    // Original object relative source line 392.
    case 0x88760369: return "No more stream handles";
    // Original object relative source line 395.
    case 0x8876036C: return "No internet";
    // Original object relative source line 402.
    case 0x88760818: return "Wrong texture format";
    // Original object relative source line 403.
    case 0x88760819: return "Unsupported color operation";
    // Original object relative source line 404.
    case 0x8876081A: return "Unsupported color arg";
    // Original object relative source line 405.
    case 0x8876081B: return "Unsupported alpha operation";
    // Original object relative source line 406.
    case 0x8876081C: return "Unsupported alpha arg";
    // Original object relative source line 407.
    case 0x8876081D: return "Too many operations";
    // Original object relative source line 408.
    case 0x8876081E: return "Conflicting texture filter";
    // Original object relative source line 409.
    case 0x8876081F: return "Unsupported factor value";
    // Original object relative source line 410.
    case 0x88760821: return "Conflicting render state";
    // Original object relative source line 411.
    case 0x88760822: return "Unsupported texture filter";
    // Original object relative source line 412.
    case 0x88760826: return "Conflicting texture palette";
    // Original object relative source line 413.
    case 0x88760827: return "Driver internal error";
    // Original object relative source line 415.
    case 0x88760867: return "More data";
    // Original object relative source line 416.
    case 0x88760868: return "Device lost";
    // Original object relative source line 417.
    case 0x88760869: return "Device not reset";
    // Original object relative source line 418.
    case 0x8876086A: return "Not available";
    // Original object relative source line 419.
    case 0x8876017C: return "Out of video memory";
    // Original object relative source line 420.
    case 0x8015017C:
    case 0x8876086B: return "Invalid device";
    // Original object relative source line 421.
    case 0x8876086C: return "Invalid call";
    // Original object relative source line 422.
    case 0x8876086D: return "Driver invalid call";
    // Original object relative source line 429.
    case 0x0876086F: return "The call succeeded but there won't be any mipmaps generated";
    // Original object relative source line 435.
    case 0x88760B54: return "Can not modify index buffer";
    // Original object relative source line 436.
    case 0x88760B55: return "Invalid mesh";
    // Original object relative source line 437.
    case 0x88760B56: return "Cannot attr sort";
    // Original object relative source line 438.
    case 0x88760B57: return "Skinning not supported";
    // Original object relative source line 439.
    case 0x88760B58: return "Too many influences";
    // Original object relative source line 440.
    case 0x88760B59: return "Invalid data";
    // Original object relative source line 441.
    case 0x88760B5A: return "Loaded mesh has no data";
    // Original object relative source line 442.
    case 0x88760B5B: return "Duplicate named fragment";
    // Original object relative source line 443.
    case 0x88760B5C: return "Can Not remove last item";
    // Original object relative source line 449.
    case 0xC8770BB8: return "Out of memory";
    // Original object relative source line 450.
    case 0xC8770BB9: return "A NULL pointer was passed as a parameter";
    // Original object relative source line 451.
    case 0xC8770BBA: return "The Device Index passed in is invalid";
    // Original object relative source line 452.
    case 0xC8770BBB: return "DirectDraw has not been created";
    // Original object relative source line 453.
    case 0xC8770BBC: return "Direct3D has not been created";
    // Original object relative source line 454.
    case 0xC8770BBD: return "Direct3D device has not been created";
    // Original object relative source line 455.
    case 0xC8770BBE: return "Primary surface has not been created";
    // Original object relative source line 456.
    case 0xC8770BBF: return "Z buffer has not been created";
    // Original object relative source line 457.
    case 0xC8770BC0: return "Backbuffer has not been created";
    // Original object relative source line 458.
    case 0xC8770BC1: return "Failed to update caps database after changing display mode";
    // Original object relative source line 459.
    case 0xC8770BC2: return "Could not create Z buffer";
    // Original object relative source line 460.
    case 0xC8770BC3: return "Display mode is not valid";
    // Original object relative source line 461.
    case 0xC8770BC4: return "One or more of the parameters passed is invalid";
    // Original object relative source line 462.
    case 0xC8770BC5: return "D3DX failed to initialize itself";
    // Original object relative source line 463.
    case 0xC8770BC6: return "D3DX failed to start up";
    // Original object relative source line 464.
    case 0xC8770BC7: return "D3DXInitialize() must be called first";
    // Original object relative source line 465.
    case 0xC8770BC8: return "D3DX is not initialized yet";
    // Original object relative source line 466.
    case 0xC8770BC9: return "Failed to render text to the surface";
    // Original object relative source line 467.
    case 0xC8770BCA: return "Bad D3DX context";
    // Original object relative source line 468.
    case 0xC8770BCB: return "The requested device capabilities are not supported";
    // Original object relative source line 469.
    case 0xC8770BCC: return "The image file format is unrecognized";
    // Original object relative source line 470.
    case 0xC8770BCD: return "The image file loading library error";
    // Original object relative source line 471.
    case 0xC8770BCE: return "Could not obtain device caps";
    // Original object relative source line 472.
    case 0xC8770BCF: return "Resize does not work for full-screen";
    // Original object relative source line 473.
    case 0xC8770BD0: return "Resize does not work for non-windowed contexts";
    // Original object relative source line 474.
    case 0xC8770BD1: return "Front buffer already exists";
    // Original object relative source line 475.
    case 0xC8770BD2: return "The app is using the primary in full-screen mode";
    // Original object relative source line 476.
    case 0xC8770BD3: return "Could not get device context";
    // Original object relative source line 477.
    case 0xC8770BD4: return "Could not bitBlt";
    // Original object relative source line 478.
    case 0xC8770BD5: return "There is no surface backing up this texture";
    // Original object relative source line 479.
    case 0xC8770BD6: return "There is no such miplevel for this surface";
    // Original object relative source line 480.
    case 0xC8770BD7: return "The surface is not paletted";
    // Original object relative source line 481.
    case 0xC8770BD8: return "An error occured while enumerating surface formats";
    // Original object relative source line 482.
    case 0xC8770BD9: return "D3DX only supports color depths of 16 bit or greater";
    // Original object relative source line 483.
    case 0xC8770BDA: return "The file format is invalid";
    // Original object relative source line 484.
    case 0xC8770BDB: return "No suitable match found";
    // Original object relative source line 490.
    case 0x88760384: return "Bad object";
    // Original object relative source line 491.
    case 0x88760385: return "Bad value";
    // Original object relative source line 492.
    case 0x88760386: return "Bad type";
    // Original object relative source line 493.
    case 0x88760387:
    case 0x88760866: return "Not found";
    // Original object relative source line 494.
    case 0x88760388: return "Not done yet";
    // Original object relative source line 495.
    case 0x88760389: return "File not found";
    // Original object relative source line 496.
    case 0x8876038A: return "Resource not found";
    // Original object relative source line 497.
    case 0x8876038B: return "Bad resource";
    // Original object relative source line 498.
    case 0x8876038C: return "Bad file type";
    // Original object relative source line 499.
    case 0x8876038D: return "Bad file version";
    // Original object relative source line 500.
    case 0x8876038E: return "Bad file float size";
    // Original object relative source line 501.
    case 0x8876038F: return "Bad file";
    // Original object relative source line 502.
    case 0x88760390: return "Parse error";
    // Original object relative source line 503.
    case 0x88760364:
    case 0x88760391: return "Bad array size";
    // Original object relative source line 504.
    case 0x88760365:
    case 0x88760392: return "Bad data reference";
    // Original object relative source line 505.
    case 0x88760367:
    case 0x88760393: return "No more objects";
    // Original object relative source line 506.
    case 0x8876036A:
    case 0x88760394: return "No more data";
    // Original object relative source line 507.
    case 0x8876036B:
    case 0x88760395: return "Bad cache file";
    // Original object relative source line 514.
    case 0x0878000A: return "The call succeeded, but we had to substitute the 3D algorithm";
    // Original object relative source line 516.
    case 0x8878000A: return "The call failed because resources (such as a priority level) were already being used by another caller";
    // Original object relative source line 517.
    case 0x8878001E: return "The control (vol, pan, etc.) requested by the caller is not available";
    // Original object relative source line 519.
    case 0x88780032: return "This call is not valid for the current state of this object";
    // Original object relative source line 521.
    case 0x88780046: return "The caller does not have the priority level required for the function to succeed";
    // Original object relative source line 523.
    case 0x88780064: return "The specified WAVE format is not supported";
    // Original object relative source line 525.
    case 0x88780078: return "No sound driver is available for use";
    // Original object relative source line 526.
    case 0x800704DF:
    case 0x88760005:
    case 0x88780082: return "This object is already initialized";
    // Original object relative source line 528.
    case 0x88780096: return "The buffer memory has been lost, and must be restored";
    // Original object relative source line 529.
    case 0x887800A0: return "Another app has a higher priority level, preventing this call from succeeding";
    // Original object relative source line 530.
    case 0x80070015:
    case 0x887800AA: return "This object has not been initialized";
    // Original object relative source line 533.
    case 0x887800B4: return "Tried to create a DSBCAPS_CTRLFX buffer shorter than DSBSIZE_FX_MIN milliseconds";
    // Original object relative source line 534.
    case 0x887800BE: return "Attempt to use DirectSound 8 functionality on an older DirectSound object";
    // Original object relative source line 535.
    case 0x887800C8: return "A circular loop of send effects was detected";
    // Original object relative source line 536.
    case 0x887800D2: return "The GUID specified in an audiopath file does not match a valid MIXIN buffer";
    // Original object relative source line 537.
    case 0x88781161: return "The object requested was not found (numerically equal to DMUS_E_NOT_FOUND)";
    // Original object relative source line 542.
    case 0x08781091: return "The object could only load partially. This can happen if some components are not registered properly, such as embedded tracks and tools. This can also happen if some content is missing. For example, if a segment uses a DLS collection that is not in the loader's current search directory.";
    // Original object relative source line 543.
    case 0x08781092: return "Return value from IDirectMusicBand::Download() which indicates that some of the instruments safely downloaded, but others failed. This usually occurs when some instruments are on PChannels not supported by the performance or port.";
    // Original object relative source line 544.
    case 0x08781200: return "Return value from IDirectMusicTool::ProcessPMsg() which indicates to the performance that it should cue the PMsg again automatically.";
    // Original object relative source line 545.
    case 0x08781201: return "Return value from IDirectMusicTool::ProcessPMsg() which indicates to the performance that it should free the PMsg automatically.";
    // Original object relative source line 546.
    case 0x08781202: return "Return value from IDirectMusicTrack::Play() which indicates to the segment that the track has no more data after mtEnd.";
    // Original object relative source line 547.
    case 0x08781210: return "Returned string has been truncated to fit the buffer size.";
    // Original object relative source line 548.
    case 0x08781211: return "Returned from IDirectMusicGraph::StampPMsg(), this indicates that the PMsg is already stamped with the last tool in the graph. The returned PMsg's tool pointer is now NULL.";
    // Original object relative source line 549.
    case 0x08781212: return "Returned from IDirectMusicPerformance::MusicToMIDI(), this indicates  that no note has been calculated because the music value has the note  at a position higher than the top note of the chord. This applies only to DMUS_PLAYMODE_NORMALCHORD play mode. This success code indicates that the caller should not do anything with the note. It is not meant to be played against this chord.";
    // Original object relative source line 550.
    case 0x08781213: return "Returned from IDirectMusicPerformance::MIDIToMusic(),  and IDirectMusicPerformance::MusicToMIDI(), this indicates  that the note conversion generated a note value that is below 0,  so it has been bumped up one or more octaves to be in the proper MIDI range of 0 through 127.  Note that this is valid for MIDIToMusic() when using play modes DMUS_PLAYMODE_FIXEDTOCHORD and DMUS_PLAYMODE_FIXEDTOKEY, both of which store MIDI values in wMusicValue. With MusicToMIDI(), it is valid for all play modes. Ofcourse, DMUS_PLAYMODE_FIXED will never return this success code.";
    // Original object relative source line 551.
    case 0x08781214: return "Returned from IDirectMusicPerformance::MIDIToMusic(),  and IDirectMusicPerformance::MusicToMIDI(), this indicates  that the note conversion generated a note value that is above 127, so it has been bumped down one or more octaves to be in the proper MIDI range of 0 through 127.  Note that this is valid for MIDIToMusic() when using play modes DMUS_PLAYMODE_FIXEDTOCHORD and DMUS_PLAYMODE_FIXEDTOKEY, both of which store MIDI values in wMusicValue. With MusicToMIDI(), it is valid for all play modes. Ofcourse, DMUS_PLAYMODE_FIXED will never return this success code.";
    // Original object relative source line 552.
    case 0x08781215: return "Although the audio output from the port will be routed to the same device as the given DirectSound buffer, buffer controls such as pan and volume will not affect the output.";
    // Original object relative source line 553.
    case 0x08781216: return "The requested operation was not performed because during CollectGarbage the loader determined that the object had been released.";
    // Original object relative source line 554.
    case 0x88781101: return "An unexpected error was returned from a device driver, indicating possible failure of the driver or hardware.";
    // Original object relative source line 555.
    case 0x88781102: return "The requested operation cannot be performed while there are  instantiated ports in any process in the system.";
    // Original object relative source line 556.
    case 0x88781103: return "The requested device is already in use (possibly by a non-DirectMusic client) and cannot be opened again.";
    // Original object relative source line 557.
    case 0x88781104: return "Buffer is not large enough for requested operation.";
    // Original object relative source line 558.
    case 0x88781105: return "No buffer was prepared for the download data.";
    // Original object relative source line 559.
    case 0x88781106: return "Download failed due to inability to access or create download buffer.";
    // Original object relative source line 560.
    case 0x88781108: return "Error parsing DLS collection. File is corrupt.";
    // Original object relative source line 561.
    case 0x88781109: return "Wave chunks in DLS collection file are at incorrect offsets.";
    // Original object relative source line 562.
    case 0x88781111: return "Second attempt to load a DLS collection that is currently open. ";
    // Original object relative source line 563.
    case 0x88781113: return "Error reading wave data from DLS collection. Indicates bad file.";
    // Original object relative source line 564.
    case 0x88781114: return "There is no instrument in the collection that matches patch number.";
    // Original object relative source line 565.
    case 0x88781115: return "The IStream* doesn't support Seek().";
    // Original object relative source line 566.
    case 0x88781116: return "The IStream* doesn't support Write().";
    // Original object relative source line 567.
    case 0x88781117: return "The RIFF parser doesn't contain a required chunk while parsing file.";
    // Original object relative source line 568.
    case 0x88781119: return "Invalid download id was used in the process of creating a download buffer.";
    // Original object relative source line 569.
    case 0x88781120: return "Tried to unload an object that was not downloaded or previously unloaded.";
    // Original object relative source line 570.
    case 0x88781121: return "Buffer was already downloaded to synth.";
    // Original object relative source line 571.
    case 0x88781122: return "The specified property item was not recognized by the target object.";
    // Original object relative source line 572.
    case 0x88781123: return "The specified property item may not be set on the target object.";
    // Original object relative source line 573.
    case 0x88781124: return "* The specified property item may not be retrieved from the target object.";
    // Original object relative source line 574.
    case 0x88781125: return "Wave chunk has more than one interleaved channel. DLS format requires MONO.";
    // Original object relative source line 575.
    case 0x88781126: return "Invalid articulation chunk in DLS collection.";
    // Original object relative source line 576.
    case 0x88781127: return "Invalid instrument chunk in DLS collection.";
    // Original object relative source line 577.
    case 0x88781128: return "Wavelink chunk in DLS collection points to invalid wave.";
    // Original object relative source line 578.
    case 0x88781129: return "Articulation missing from instrument in DLS collection.";
    // Original object relative source line 579.
    case 0x8878112A: return "Downoaded DLS wave is not in PCM format. ";
    // Original object relative source line 580.
    case 0x8878112B: return "Bad wave chunk in DLS collection";
    // Original object relative source line 581.
    case 0x8878112C: return "Offset Table for download buffer has errors. ";
    // Original object relative source line 582.
    case 0x8878112D: return "Attempted to download unknown data type.";
    // Original object relative source line 583.
    case 0x8878112E: return "The operation could not be completed because no sink was connected to the synthesizer.";
    // Original object relative source line 584.
    case 0x8878112F: return "An attempt was made to open the software synthesizer while it was already  open.";
    // Original object relative source line 585.
    case 0x88781130: return "An attempt was made to close the software synthesizer while it was already  open.";
    // Original object relative source line 586.
    case 0x88781131: return "The operation could not be completed because the software synth has not  yet been fully configured.";
    // Original object relative source line 587.
    case 0x88781132: return "The operation cannot be carried out while the synthesizer is active.";
    // Original object relative source line 588.
    case 0x88781133: return "An error occurred while attempting to read from the IStream* object.";
    // Original object relative source line 589.
    case 0x88781134: return "The operation cannot be performed because the final instance of the DirectMusic object was released. Ports cannot be used after final  release of the DirectMusic object.";
    // Original object relative source line 590.
    case 0x88781135: return "There was no data in the referenced buffer.";
    // Original object relative source line 591.
    case 0x88781136: return "There is insufficient space to insert the given event into the buffer.";
    // Original object relative source line 592.
    case 0x88781137: return "The given operation could not be carried out because the port is a capture port.";
    // Original object relative source line 593.
    case 0x88781138: return "The given operation could not be carried out because the port is a render port.";
    // Original object relative source line 594.
    case 0x88781139: return "The port could not be created because no DirectSound has been specified. Specify a DirectSound interface via the IDirectMusic::SetDirectSound method; pass NULL to have DirectMusic manage usage of DirectSound.";
    // Original object relative source line 595.
    case 0x8878113A: return "The operation cannot be carried out while the port is active.";
    // Original object relative source line 596.
    case 0x8878113B: return "Invalid DirectSound buffer was handed to port. ";
    // Original object relative source line 597.
    case 0x8878113C: return "Invalid buffer format was handed to the synth sink.";
    // Original object relative source line 598.
    case 0x8878113D: return "The operation cannot be carried out while the synthesizer is inactive.";
    // Original object relative source line 599.
    case 0x8878113E: return "IDirectMusic::SetDirectSound has already been called. It may not be changed while in use.";
    // Original object relative source line 600.
    case 0x8878113F: return "The given event is invalid (either it is not a valid MIDI message or it makes use of running status). The event cannot be packed into the buffer.";
    // Original object relative source line 601.
    case 0x88781150: return "The IStream* object does not contain data supported by the loading object.";
    // Original object relative source line 602.
    case 0x88781151: return "The object has already been initialized.";
    // Original object relative source line 603.
    case 0x88781152: return "The file does not contain a valid band.";
    // Original object relative source line 604.
    case 0x88781155: return "The IStream* object's data does not have a track header as the first chunk, and therefore can not be read by the segment object.";
    // Original object relative source line 605.
    case 0x88781156: return "The IStream* object's data does not have a tool header as the first chunk, and therefore can not be read by the graph object.";
    // Original object relative source line 606.
    case 0x88781157: return "The IStream* object's data contains an invalid track header (ckid is 0 and fccType is NULL,) and therefore can not be read by the segment object.";
    // Original object relative source line 607.
    case 0x88781158: return "The IStream* object's data contains an invalid tool header (ckid is 0 and fccType is NULL,) and therefore can not be read by the graph object.";
    // Original object relative source line 608.
    case 0x88781159: return "The graph object was unable to load all tools from the IStream* object data. This may be due to errors in the stream, or the tools being incorrectly registered on the client.";
    // Original object relative source line 609.
    case 0x88781160: return "The segment object was unable to load all tracks from the IStream* object data. This may be due to errors in the stream, or the tracks being incorrectly registered on the client.";
    // Original object relative source line 611.
    case 0x88781162: return "A required object is not initialized or failed to initialize.";
    // Original object relative source line 612.
    case 0x88781163: return "The requested parameter type is currently disabled. Parameter types may be enabled and disabled by certain calls to SetParam().";
    // Original object relative source line 613.
    case 0x88781164: return "The requested parameter type is not supported on the object.";
    // Original object relative source line 614.
    case 0x88781165: return "The time is in the past, and the operation can not succeed.";
    // Original object relative source line 615.
    case 0x88781166: return "The requested track is not contained by the segment.";
    // Original object relative source line 616.
    case 0x88781167: return "The track does not support clock time playback or getparam.";
    // Original object relative source line 617.
    case 0x88781170: return "There is no master clock in the performance. Be sure to call IDirectMusicPerformance::Init().";
    // Original object relative source line 618.
    case 0x88781180: return "The class id field is required and missing in the DMUS_OBJECTDESC.";
    // Original object relative source line 619.
    case 0x88781181: return "The requested file path is invalid.";
    // Original object relative source line 620.
    case 0x88781182: return "File open failed - either file doesn't exist or is locked.";
    // Original object relative source line 621.
    case 0x88781183: return "Search data type is not supported.";
    // Original object relative source line 622.
    case 0x88781184: return "Unable to find or create object.";
    // Original object relative source line 623.
    case 0x88781185: return "Object was not found.";
    // Original object relative source line 624.
    case 0x88781186: return "The file name is missing from the DMUS_OBJECTDESC.";
    // Original object relative source line 625.
    case 0x88781200: return "The file requested is not a valid file.";
    // Original object relative source line 626.
    case 0x88781201: return "The tool is already contained in the graph. Create a new instance.";
    // Original object relative source line 627.
    case 0x88781202: return "Value is out of range, for instance the requested length is longer than the segment.";
    // Original object relative source line 628.
    case 0x88781203: return "Segment initialization failed, most likely due to a critical memory situation.";
    // Original object relative source line 629.
    case 0x88781204: return "The DMUS_PMSG has already been sent to the performance object via IDirectMusicPerformance::SendPMsg().";
    // Original object relative source line 630.
    case 0x88781205: return "The DMUS_PMSG was either not allocated by the performance via IDirectMusicPerformance::AllocPMsg(), or it was already freed via IDirectMusicPerformance::FreePMsg().";
    // Original object relative source line 631.
    case 0x88781206: return "The default system port could not be opened.";
    // Original object relative source line 632.
    case 0x88781207: return "A call to MIDIToMusic() or MusicToMIDI() resulted in an error because the requested conversion could not happen. This usually occurs when the provided DMUS_CHORD_KEY structure has an invalid chord or scale pattern.";
    // Original object relative source line 633.
    case 0x88781210: return "DMUS_E_DESCEND_CHUNK_FAIL is returned when the end of the file  was reached before the desired chunk was found.";
    // Original object relative source line 634.
    case 0x88781211: return "An attempt to use this object failed because it first needs to be loaded.";
    // Original object relative source line 635.
    case 0x88781213: return "The activeX scripting engine for the script's language is not compatible with DirectMusic.";
    // Original object relative source line 636.
    case 0x88781214: return "A varient was used that had a type that is not supported by DirectMusic.";
    // Original object relative source line 637.
    case 0x88781215: return "An error was encountered while parsing or executing the script. The pErrorInfo parameter (if supplied) was filled with information about the error.";
    // Original object relative source line 638.
    case 0x88781216: return "Loading of oleaut32.dll failed.  VBScript and other activeX scripting languages require use of oleaut32.dll.  On platforms where oleaut32.dll is not present, only the DirectMusicScript language, which doesn't require oleaut32.dll can be used.";
    // Original object relative source line 639.
    case 0x88781217: return "An error occured while parsing a script loaded using LoadScript.  The script that was loaded contains an error.";
    // Original object relative source line 640.
    case 0x88781218: return "The script file is invalid.";
    // Original object relative source line 641.
    case 0x88781219: return "The file contains an invalid script track.";
    // Original object relative source line 642.
    case 0x8878121A: return "The script does not contain a variable with the specified name.";
    // Original object relative source line 643.
    case 0x8878121B: return "The script does not contain a routine with the specified name.";
    // Original object relative source line 644.
    case 0x8878121C: return "Scripts variables for content referenced or embedded in a script cannot be set.";
    // Original object relative source line 645.
    case 0x8878121D: return "Attempt was made to set a script's variable by reference to a value that was not an object type.";
    // Original object relative source line 646.
    case 0x8878121E: return "Attempt was made to set a script's variable by value to an object that does not support a default value property.";
    // Original object relative source line 647.
    case 0x88781220: return "The file contains an invalid segment trigger track.";
    // Original object relative source line 648.
    case 0x88781221: return "The file contains an invalid lyrics track.";
    // Original object relative source line 649.
    case 0x88781222: return "The file contains an invalid parameter control track.";
    // Original object relative source line 650.
    case 0x88781223: return "A script written in AudioVBScript could not be read because it contained a statement that is not allowed by the AudioVBScript language.";
    // Original object relative source line 651.
    case 0x88781224: return "A script routine written in AudioVBScript failed because an invalid operation occurred.  For example, adding the number 3 to a segment object would produce this error.  So would attempting to call a routine that doesn't exist.";
    // Original object relative source line 652.
    case 0x88781225: return "A script routine written in AudioVBScript failed because a function outside of a script failed to complete. For example, a call to PlaySegment that fails to play because of low memory would return this error.";
    // Original object relative source line 653.
    case 0x88781226: return "The Performance has set up some PChannels using the AssignPChannel command, which makes it not capable of supporting audio paths.";
    // Original object relative source line 654.
    case 0x88781227: return "This is the inverse of the previous error. The Performance has set up some audio paths, which makes is incompatible with the calls to allocate pchannels, etc. ";
    // Original object relative source line 655.
    case 0x88781228: return "A segment or song was asked for its embedded audio path configuration, but there isn't any. ";
    // Original object relative source line 656.
    case 0x88781229: return "An audiopath is inactive, perhaps because closedown was called.";
    // Original object relative source line 657.
    case 0x8878122A: return "An audiopath failed to create because a requested buffer could not be created.";
    // Original object relative source line 658.
    case 0x8878122B: return "An audiopath could not be used for playback because it lacked port assignments.";
    // Original object relative source line 659.
    case 0x8878122C: return "Attempt was made to play segment in audiopath mode and there was no audiopath.";
    // Original object relative source line 660.
    case 0x8878122D: return "Invalid data was found in a RIFF file chunk.";
    // Original object relative source line 661.
    case 0x8878122E: return "Attempt was made to create an audiopath that sends to a global effects buffer which did not exist.";
    // Original object relative source line 662.
    case 0x8878122F: return "The file does not contain a valid container object.";
    // Original object relative source line 679.
    case 0x8004020C: return "No buffer space has been set";
    // Original object relative source line 680.
    case 0x8004020D: return "The buffer is not big enough.";
    // Original object relative source line 681.
    case 0x8004020E: return "An invalid alignment was specified.";
    // Original object relative source line 682.
    case 0x8004020F: return "Cannot change allocated memory while the filter is active.";
    // Original object relative source line 683.
    case 0x80040210: return "One or more buffers are still active.";
    // Original object relative source line 684.
    case 0x80040211: return "Cannot allocate a sample when the allocator is not active.";
    // Original object relative source line 685.
    case 0x80040212: return "Cannot allocate memory because no size has been set.";
    // Original object relative source line 686.
    case 0x80040213: return "Cannot lock for synchronization because no clock has been defined.";
    // Original object relative source line 687.
    case 0x80040214: return "Quality messages could not be sent because no quality sink has been defined.";
    // Original object relative source line 688.
    case 0x80040215: return "A required interface has not been implemented.";
    // Original object relative source line 689.
    case 0x80040216: return "An object or name was not found.";
    // Original object relative source line 690.
    case 0x80040217: return "No combination of intermediate filters could be found to make the connection.";
    // Original object relative source line 691.
    case 0x80040218: return "No combination of filters could be found to render the stream.";
    // Original object relative source line 692.
    case 0x80040219: return "Could not change formats dynamically.";
    // Original object relative source line 693.
    case 0x8004021A: return "No color key has been set.";
    // Original object relative source line 694.
    case 0x8004021B: return "Current pin connection is not using the IOverlay transport.";
    // Original object relative source line 695.
    case 0x8004021C: return "Current pin connection is not using the IMemInputPin transport.";
    // Original object relative source line 696.
    case 0x8004021D: return "Setting a color key would conflict with the palette already set.";
    // Original object relative source line 697.
    case 0x8004021E: return "Setting a palette would conflict with the color key already set.";
    // Original object relative source line 698.
    case 0x8004021F: return "No matching color key is available.";
    // Original object relative source line 699.
    case 0x80040220: return "No palette is available.";
    // Original object relative source line 700.
    case 0x80040221: return "Display does not use a palette.";
    // Original object relative source line 701.
    case 0x80040222: return "Too many colors for the current display settings.";
    // Original object relative source line 702.
    case 0x80040223: return "The state changed while waiting to process the sample.";
    // Original object relative source line 703.
    case 0x80040224: return "The operation could not be performed because the filter is not stopped.";
    // Original object relative source line 704.
    case 0x80040225: return "The operation could not be performed because the filter is not paused.";
    // Original object relative source line 705.
    case 0x80040226: return "The operation could not be performed because the filter is not running.";
    // Original object relative source line 706.
    case 0x80040227: return "The operation could not be performed because the filter is in the wrong state.";
    // Original object relative source line 707.
    case 0x80040228: return "The sample start time is after the sample end time.";
    // Original object relative source line 708.
    case 0x80040229: return "The supplied rectangle is invalid.";
    // Original object relative source line 709.
    case 0x8004022A: return "This pin cannot use the supplied media type.";
    // Original object relative source line 710.
    case 0x8004022B: return "This sample cannot be rendered.";
    // Original object relative source line 711.
    case 0x8004022C: return "This sample cannot be rendered because the end of the stream has been reached.";
    // Original object relative source line 712.
    case 0x8004022D: return "An attempt to add a filter with a duplicate name failed.";
    // Original object relative source line 713.
    case 0x0004022D: return "An attempt to add a filter with a duplicate name succeeded with a modified name.";
    // Original object relative source line 714.
    case 0x8004022E: return "A time-out has expired.";
    // Original object relative source line 715.
    case 0x8004022F: return "The file format is invalid.";
    // Original object relative source line 716.
    case 0x80040230: return "The list has already been exhausted.";
    // Original object relative source line 717.
    case 0x80040231: return "The filter graph is circular.";
    // Original object relative source line 718.
    case 0x80040232: return "Updates are not allowed in this state.";
    // Original object relative source line 719.
    case 0x80040233: return "An attempt was made to queue a command for a time in the past.";
    // Original object relative source line 720.
    case 0x80040234: return "The queued command has already been canceled.";
    // Original object relative source line 721.
    case 0x80040235: return "Cannot render the file because it is corrupt.";
    // Original object relative source line 722.
    case 0x80040236: return "An overlay advise link already exists.";
    // Original object relative source line 723.
    case 0x00040237: return "The state transition has not completed.";
    // Original object relative source line 724.
    case 0x80040238: return "No full-screen modes are available.";
    // Original object relative source line 725.
    case 0x80040239: return "This Advise cannot be canceled because it was not successfully set.";
    // Original object relative source line 726.
    case 0x8004023A: return "A full-screen mode is not available.";
    // Original object relative source line 727.
    case 0x8004023B: return "Cannot call IVideoWindow methods while in full-screen mode.";
    // Original object relative source line 728.
    case 0x80040240: return "The media type of this file is not recognized.";
    // Original object relative source line 729.
    case 0x80040241: return "The source filter for this file could not be loaded.";
    // Original object relative source line 730.
    case 0x00040242: return "Some of the streams in this movie are in an unsupported format.";
    // Original object relative source line 731.
    case 0x80040243: return "A file appeared to be incomplete.";
    // Original object relative source line 732.
    case 0x80040244: return "The version number of the file is invalid.";
    // Original object relative source line 733.
    case 0x00040245: return "The file contained some property settings that were not used.";
    // Original object relative source line 734.
    case 0x00040246: return "Some connections have failed and have been deferred.";
    // Original object relative source line 735.
    case 0x80040247: return "This file is corrupt: it contains an invalid class identifier.";
    // Original object relative source line 736.
    case 0x80040248: return "This file is corrupt: it contains an invalid media type.";
    // Original object relative source line 737.
    case 0x800403F2: return "A registry entry is corrupt.";
    // Original object relative source line 738.
    case 0x00040103: return "The end of the list has been reached.";
    // Original object relative source line 739.
    case 0x80040249: return "No time stamp has been set for this sample.";
    // Original object relative source line 740.
    case 0x00040250: return "The resource specified is no longer needed.";
    // Original object relative source line 741.
    case 0x80040251: return "No media time stamp has been set for this sample.";
    // Original object relative source line 742.
    case 0x80040252: return "No media time format has been selected.";
    // Original object relative source line 743.
    case 0x80040253: return "Cannot change balance because audio device is mono only.";
    // Original object relative source line 744.
    case 0x00040254: return "A connection could not be made with the media type in the persistent graph, but has been made with a negotiated media type.";
    // Original object relative source line 746.
    case 0x80040256: return "Cannot play back the audio stream: no audio hardware is available, or the hardware is not responding.";
    // Original object relative source line 747.
    case 0x00040257:
    case 0x80040255: return "Cannot play back the video stream: no suitable decompressor could be found.";
    // Original object relative source line 748.
    case 0x00040258: return "Cannot play back the audio stream: no audio hardware is available.";
    // Original object relative source line 750.
    case 0x0004025A:
    case 0x80040259: return "Cannot play back the video stream: format 'RPZA' is not supported.";
    // Original object relative source line 751.
    case 0x8004025B: return "ActiveMovie cannot play MPEG movies on this processor.";
    // Original object relative source line 752.
    case 0x8004025C: return "Cannot play back the audio stream: the audio format is not supported.";
    // Original object relative source line 753.
    case 0x8004025D: return "Cannot play back the video stream: the video format is not supported.";
    // Original object relative source line 754.
    case 0x8004025E: return "ActiveMovie cannot play this video stream because it falls outside the constrained standard.";
    // Original object relative source line 755.
    case 0x8004025F: return "Cannot perform the requested function on an object that is not in the filter graph.";
    // Original object relative source line 756.
    case 0x00040260: return "The value returned had to be estimated.  It's accuracy can not be guaranteed.";
    // Original object relative source line 757.
    case 0x80040261: return "Cannot get or set time related information on an object that is using a time format of TIME_FORMAT_NONE.";
    // Original object relative source line 758.
    case 0x80040262: return "The connection cannot be made because the stream is read only and the filter alters the data.";
    // Original object relative source line 759.
    case 0x00040263: return "This success code is reserved for internal purposes within ActiveMovie.";
    // Original object relative source line 760.
    case 0x80040264: return "The buffer is not full enough.";
    // Original object relative source line 761.
    case 0x80040265: return "Cannot play back the file.  The format is not supported.";
    // Original object relative source line 762.
    case 0x80040266: return "Pins cannot connect due to not supporting the same transport.";
    // Original object relative source line 763.
    case 0x00040267: return "The stream has been turned off.";
    // Original object relative source line 764.
    case 0x00040268: return "The graph can't be cued because of lack of or corrupt data.";
    // Original object relative source line 765.
    case 0x80040269: return "The Video CD can't be read correctly by the device or is the data is corrupt.";
    // Original object relative source line 766.
    case 0x00040270: return "The stop time for the sample was not set.";
    // Original object relative source line 767.
    case 0x80040271: return "There is not enough Video Memory at this display resolution and number of colors. Reducing resolution might help.";
    // Original object relative source line 768.
    case 0x80040272: return "The VideoPort connection negotiation process has failed.";
    // Original object relative source line 769.
    case 0x80040273: return "Either DirectDraw has not been installed or the Video Card capabilities are not suitable. Make sure the display is not in 16 color mode.";
    // Original object relative source line 770.
    case 0x80040274: return "No VideoPort hardware is available, or the hardware is not responding.";
    // Original object relative source line 771.
    case 0x80040275: return "No Capture hardware is available, or the hardware is not responding.";
    // Original object relative source line 772.
    case 0x80040276: return "This User Operation is inhibited by DVD Content at this time.";
    // Original object relative source line 773.
    case 0x80040277: return "This Operation is not permitted in the current domain.";
    // Original object relative source line 774.
    case 0x80040278: return "The specified button is invalid or is not present at the current time, or there is no button present at the specified location.";
    // Original object relative source line 775.
    case 0x80040279: return "DVD-Video playback graph has not been built yet.";
    // Original object relative source line 776.
    case 0x8004027A: return "DVD-Video playback graph building failed.";
    // Original object relative source line 777.
    case 0x8004027B: return "DVD-Video playback graph could not be built due to insufficient decoders.";
    // Original object relative source line 778.
    case 0x8004027C: return "Version number of DirectDraw not suitable. Make sure to install dx5 or higher version.";
    // Original object relative source line 779.
    case 0x8004027D: return "Copy protection cannot be enabled. Please make sure any other copy protected content is not being shown now.";
    // Original object relative source line 780.
    case 0x0004027E: return "There was no preview pin available, so the capture pin output is being split to provide both capture and preview.";
    // Original object relative source line 781.
    case 0x8004027F: return "This object cannot be used anymore as its time has expired.";
    // Original object relative source line 782.
    case 0x00040280: return "The current title was not a sequential set of chapters (PGC), and the returned timing information might not be continuous.";
    // Original object relative source line 783.
    case 0x80040281: return "The operation cannot be performed at the current playback speed.";
    // Original object relative source line 784.
    case 0x80040282: return "The specified menu doesn't exist.";
    // Original object relative source line 785.
    case 0x80040283: return "The specified command was either cancelled or no longer exists.";
    // Original object relative source line 786.
    case 0x80040284: return "The data did not contain a recognized version.";
    // Original object relative source line 787.
    case 0x80040285: return "The state data was corrupt.";
    // Original object relative source line 788.
    case 0x80040286: return "The state data is from a different disc.";
    // Original object relative source line 789.
    case 0x80040287: return "The region was not compatible with the current drive.";
    // Original object relative source line 790.
    case 0x80040288: return "The requested DVD stream attribute does not exist.";
    // Original object relative source line 791.
    case 0x80040289: return "Currently there is no GoUp (Annex J user function) program chain (PGC).";
    // Original object relative source line 792.
    case 0x8004028A: return "The current parental level was too low.";
    // Original object relative source line 793.
    case 0x8004028B: return "The current audio is not karaoke content.";
    // Original object relative source line 794.
    case 0x0004028C: return "The audio stream did not contain sufficient information to determine the contents of each channel.";
    // Original object relative source line 795.
    case 0x0004028D: return "The seek into the movie was not frame accurate.";
    // Original object relative source line 796.
    case 0x8004028E: return "Frame step is not supported on this configuration.";
    // Original object relative source line 797.
    case 0x8004028F: return "The specified stream is disabled and cannot be selected.";
    // Original object relative source line 798.
    case 0x80040290: return "The operation depends on the current title number, however the navigator has not yet entered the VTSM or the title domains, so the 'current' title index is unknown.";
    // Original object relative source line 799.
    case 0x80040291: return "The specified path does not point to a valid DVD disc.";
    // Original object relative source line 800.
    case 0x80040292: return "There is currently no resume information.";
    // Original object relative source line 801.
    case 0x80040293: return "This thread has already blocked this output pin.  There is no need to call IPinFlowControl::Block() again.";
    // Original object relative source line 802.
    case 0x80040294: return "IPinFlowControl::Block() has been called on another thread.  The current thread cannot make any assumptions about this pin's block state.";
    // Original object relative source line 803.
    case 0x80040295: return "An operation failed due to a certification failure.";
    // Original object relative source line 804.
    case 0x80070492: return "The specified property set is not supported.";
    // Original object relative source line 805.
    case 0x80070490: return "The specified property ID is not supported for the specified property set.";
    // Original object relative source line 812.
    case 0x00040003: return "End of stream. Sample not updated.";
    // Original object relative source line 815.
    case 0x80040403: return "No stream can be found with the specified attributes.";
    // Original object relative source line 816.
    case 0x80040404: return "Seeking not supported for this object.";
    // Original object relative source line 817.
    case 0x80040405: return "The stream formats are not compatible.";
    // Original object relative source line 818.
    case 0x80040406: return "The sample is busy.";
    // Original object relative source line 819.
    case 0x80040407: return "The object can't accept the call because its initialize function or equivalent has not been called.";
    // Original object relative source line 820.
    case 0x80040408: return "MS_E_SOURCEALREADYDEFINED";
    // Original object relative source line 821.
    case 0x80040409: return "The stream type is not valid for this operation.";
    // Original object relative source line 822.
    case 0x8004040A: return "The object is not in running state.";
    default: return "n/a";
    }
}
