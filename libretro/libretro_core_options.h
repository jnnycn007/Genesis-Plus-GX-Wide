#ifndef LIBRETRO_CORE_OPTIONS_H__
#define LIBRETRO_CORE_OPTIONS_H__

#include <stdlib.h>
#include <string.h>

#include <libretro.h>
#include <retro_inline.h>

#ifndef HAVE_NO_LANGEXTRA
#include "libretro_core_options_intl.h"
#endif

/*
 ********************************
 * VERSION: 1.3
 ********************************
 *
 * - 1.3: Move translations to libretro_core_options_intl.h
 *        - libretro_core_options_intl.h includes BOM and utf-8
 *          fix for MSVC 2010-2013
 *        - Added HAVE_NO_LANGEXTRA flag to disable translations
 *          on platforms/compilers without BOM support
 * - 1.2: Use core options v1 interface when
 *        RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION is >= 1
 *        (previously required RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION == 1)
 * - 1.1: Support generation of core options v0 retro_core_option_value
 *        arrays containing options with a single value
 * - 1.0: First commit
*/

#ifdef __cplusplus
extern "C" {
#endif

/*
 ********************************
 * Core Definitions
 ********************************
*/

#if defined(M68K_OVERCLOCK_SHIFT) || defined(Z80_OVERCLOCK_SHIFT)
#define HAVE_OVERCLOCK
#endif

/*
 ********************************
 * Core Option Definitions
 ********************************
*/

/* RETRO_LANGUAGE_ENGLISH */

/* Default language:
 * - All other languages must include the same keys and values
 * - Will be used as a fallback in the event that frontend language
 *   is not available
 * - Will be used as a fallback for any missing entries in
 *   frontend language definition */

struct retro_core_option_definition option_defs_us[] = {
   {
      CORE_NAME "_system_hw",
      "System Hardware",
      "Runs loaded content with a specific emulated console. 'Auto' will select the most appropriate system for the current game.",
      {
         { "auto",                 "Auto"               },
         { "sg-1000",              "SG-1000"            },
         { "sg-1000 II",           "SG-1000 II"         },
         { "mark-III",             "Mark III"           },
         { "master system",        "Master System"      },
         { "master system II",     "Master System II"   },
         { "game gear",            "Game Gear"          },
         { "mega drive / genesis", "Mega Drive/Genesis" },
         { NULL, NULL },
      },
      "auto"
   },
   {
      CORE_NAME "_region_detect",
      "System Region",
      "Specify which region the system is from. For consoles other than the Game Gear, 'PAL' is 50hz while 'NTSC' is 60hz. Games may run faster or slower than normal if the incorrect region is selected.",
      {
         { "auto",    "Auto"   },
         { "ntsc-u",  "NTSC-U" },
         { "pal",     "PAL"    },
         { "ntsc-j",  "NTSC-J" },
         { NULL, NULL },
      },
      "auto"
   },
   {
      CORE_NAME "_force_dtack",
      "System Lock-Ups",
      "Emulate system lock-ups that occur on real hardware when performing illegal address access. This should only be disabled when playing certain demos and homebrew that rely on illegal behaviour for correct operation.",
      {
         { "enabled",  NULL },
         { "disabled", NULL },
         { NULL, NULL },
      },
      "enabled"
   },
   {
      CORE_NAME "_bios",
      "System Boot ROM",
      "Use official BIOS/bootloader for emulated hardware, if present in RetroArch's system directory. Displays console-specific start-up sequence/animation, then runs loaded content.",
      {
         { "disabled", NULL },
         { "enabled",  NULL },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      CORE_NAME "_bram",
      "CD System BRAM",
      "When running Sega CD content, specifies whether to share a single save file between all games from a specific region (Per-BIOS) or to create a separate save file for each game (Per-Game). Note that the Sega CD has limited internal storage, sufficient only for a handful of titles. To avoid running out of space, the 'Per-Game' setting is recommended.",
      {
         { "per bios", "Per-BIOS" },
         { "per game", "Per-Game" },
         { NULL, NULL },
      },
      "per bios"
   },
   {
      CORE_NAME "_addr_error",
      "68K Address Error",
      "The Genesis CPU (Motorola 68000) produces an Address Error (crash) when attempting to perform unaligned memory access. Enabling '68K Address Error' simulates this behaviour. It should only be disabled when playing ROM hacks, since these are typically developed using less accurate emulators and may rely on invalid RAM access for correct operation.",
      {
         { "enabled",  NULL },
         { "disabled", NULL },
         { NULL, NULL },
      },
      "enabled"
   },
   {
      CORE_NAME "_lock_on",
      "Cartridge Lock-On",
      "Lock-On Technology is a Genesis feature that allowed an older game to connect to the pass-through port of a special cartridge for extended or altered gameplay. This option specifies which type of special 'lock-on' cartridge to emulate. A corresponding bios file must be present in RetroArch's system directory.",
      {
         { "disabled",            NULL },
         { "game genie",          "Game Genie" },
         { "action replay (pro)", "Action Replay (Pro)" },
         { "sonic & knuckles",    "Sonic & Knuckles" },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      CORE_NAME "_ym2413",
      "Master System FM (YM2413)",
      "Enable emulation of the FM Sound Unit used by certain Sega Mark III/Master System games for enhanced audio output.",
      {
         { "auto",     "Auto" },
         { "disabled", NULL },
         { "enabled",  NULL },
         { NULL, NULL },
      },
      "auto"
   },
   {
      CORE_NAME "_ym2612",
      "Mega Drive / Genesis FM",
#ifdef HAVE_YM3438_CORE
      "Select method used to emulate the FM synthesizer (main sound generator) of the Mega Drive/Genesis. 'MAME' options are fast, and run full speed on most systems. 'Nuked' options are cycle accurate, very high quality, and have substantial CPU requirements. The 'YM2612' chip is used by the original Model 1 Genesis. The 'YM3438' is used in later Genesis revisions.",
#else
      "Select method used to emulate the FM synthesizer (main sound generator) of the Mega Drive/Genesis. The 'YM2612' chip is used by the original Model 1 Genesis. The 'YM3438' is used in later Genesis revisions.",
#endif
      {
         { "mame (ym2612)",          "MAME (YM2612)" },
         { "mame (asic ym3438)",     "MAME (ASIC YM3438)" },
         { "mame (enhanced ym3438)", "MAME (Enhanced YM3438)" },
#ifdef HAVE_YM3438_CORE
         { "nuked (ym2612)",         "Nuked (YM2612)" },
         { "nuked (ym3438)",         "Nuked (YM3438)" },
#endif
         { NULL, NULL },
      },
      "mame (ym2612)"
   },
   {
      CORE_NAME "_sound_output",
      "Sound Output",
      "Select stereo or mono sound reproduction.",
      {
         { "stereo", "Stereo" },
         { "mono",   "Mono" },
         { NULL, NULL },
      },
      "stereo"
   },
   {
      CORE_NAME "_psg_preamp",
      "PSG Preamp Level",
      "Set the audio preamplifier level of the emulated SN76496 4-channel Programmable Sound Generator found in the Master System, Game Gear and Genesis.",
      {
         { "0",   NULL },
         { "5",   NULL },
         { "10",  NULL },
         { "15",  NULL },
         { "20",  NULL },
         { "25",  NULL },
         { "30",  NULL },
         { "35",  NULL },
         { "40",  NULL },
         { "45",  NULL },
         { "50",  NULL },
         { "55",  NULL },
         { "60",  NULL },
         { "65",  NULL },
         { "70",  NULL },
         { "75",  NULL },
         { "80",  NULL },
         { "85",  NULL },
         { "90",  NULL },
         { "95",  NULL },
         { "100", NULL },
         { "105", NULL },
         { "110", NULL },
         { "115", NULL },
         { "120", NULL },
         { "125", NULL },
         { "130", NULL },
         { "135", NULL },
         { "140", NULL },
         { "145", NULL },
         { "150", NULL },
         { "155", NULL },
         { "160", NULL },
         { "165", NULL },
         { "170", NULL },
         { "175", NULL },
         { "180", NULL },
         { "185", NULL },
         { "190", NULL },
         { "195", NULL },
         { "200", NULL },
         { NULL, NULL },
      },
      "150"
   },
   {
      CORE_NAME "_fm_preamp",
      "FM Preamp Level",
      "Set the audio preamplifier level of the emulated Sega Mark III/Master System FM Sound Unit.",
      {
         { "0",   NULL },
         { "5",   NULL },
         { "10",  NULL },
         { "15",  NULL },
         { "20",  NULL },
         { "25",  NULL },
         { "30",  NULL },
         { "35",  NULL },
         { "40",  NULL },
         { "45",  NULL },
         { "50",  NULL },
         { "55",  NULL },
         { "60",  NULL },
         { "65",  NULL },
         { "70",  NULL },
         { "75",  NULL },
         { "80",  NULL },
         { "85",  NULL },
         { "90",  NULL },
         { "95",  NULL },
         { "100", NULL },
         { "105", NULL },
         { "110", NULL },
         { "115", NULL },
         { "120", NULL },
         { "125", NULL },
         { "130", NULL },
         { "135", NULL },
         { "140", NULL },
         { "145", NULL },
         { "150", NULL },
         { "155", NULL },
         { "160", NULL },
         { "165", NULL },
         { "170", NULL },
         { "175", NULL },
         { "180", NULL },
         { "185", NULL },
         { "190", NULL },
         { "195", NULL },
         { "200", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_audio_filter",
      "Audio Filter",
      "Enable a low pass audio filter to better simulate the characteristic sound of a Model 1 Genesis.",
      {
         { "disabled", NULL },
         { "low-pass", "Low-Pass" },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      CORE_NAME "_lowpass_range",
      "Low-Pass Filter %",
      "Specify the cut-off frequency of the audio low pass filter. A higher value increases the perceived 'strength' of the filter, since a wider range of the high frequency spectrum is attenuated.",
      {
         { "5",  NULL },
         { "10", NULL },
         { "15", NULL },
         { "20", NULL },
         { "25", NULL },
         { "30", NULL },
         { "35", NULL },
         { "40", NULL },
         { "45", NULL },
         { "50", NULL },
         { "55", NULL },
         { "60", NULL },
         { "65", NULL },
         { "70", NULL },
         { "75", NULL },
         { "80", NULL },
         { "85", NULL },
         { "90", NULL },
         { "95", NULL },
         { NULL, NULL },
      },
      "60"
   },
#ifdef HAVE_EQ
   {
      CORE_NAME "_audio_eq_low",
      "EQ Low",
      "Adjust the low range band of the internal audio equaliser.",
      {
         { "0",   NULL },
         { "5",   NULL },
         { "10",  NULL },
         { "15",  NULL },
         { "20",  NULL },
         { "25",  NULL },
         { "30",  NULL },
         { "35",  NULL },
         { "40",  NULL },
         { "45",  NULL },
         { "50",  NULL },
         { "55",  NULL },
         { "60",  NULL },
         { "65",  NULL },
         { "70",  NULL },
         { "75",  NULL },
         { "80",  NULL },
         { "85",  NULL },
         { "90",  NULL },
         { "95",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_audio_eq_mid",
      "EQ Mid",
      "Adjust the middle range band of the internal audio equaliser.",
      {
         { "0",   NULL },
         { "5",   NULL },
         { "10",  NULL },
         { "15",  NULL },
         { "20",  NULL },
         { "25",  NULL },
         { "30",  NULL },
         { "35",  NULL },
         { "40",  NULL },
         { "45",  NULL },
         { "50",  NULL },
         { "55",  NULL },
         { "60",  NULL },
         { "65",  NULL },
         { "70",  NULL },
         { "75",  NULL },
         { "80",  NULL },
         { "85",  NULL },
         { "90",  NULL },
         { "95",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_audio_eq_high",
      "EQ High",
      "Adjust the high range band of the internal audio equaliser.",
      {
         { "0",   NULL },
         { "5",   NULL },
         { "10",  NULL },
         { "15",  NULL },
         { "20",  NULL },
         { "25",  NULL },
         { "30",  NULL },
         { "35",  NULL },
         { "40",  NULL },
         { "45",  NULL },
         { "50",  NULL },
         { "55",  NULL },
         { "60",  NULL },
         { "65",  NULL },
         { "70",  NULL },
         { "75",  NULL },
         { "80",  NULL },
         { "85",  NULL },
         { "90",  NULL },
         { "95",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
#endif
   {
      CORE_NAME "_frameskip",
      "Frameskip",
      "Skip frames to avoid audio buffer under-run (crackling). Improves performance at the expense of visual smoothness. 'Auto' skips frames when advised by the frontend. 'Manual' utilises the 'Frameskip Threshold (%)' setting.",
      {
         { "disabled", NULL },
         { "auto",     "Auto" },
         { "manual",   "Manual" },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      CORE_NAME "_frameskip_threshold",
      "Frameskip Threshold (%)",
      "When 'Frameskip' is set to 'Manual', specifies the audio buffer occupancy threshold (percentage) below which frames will be skipped. Higher values reduce the risk of crackling by causing frames to be dropped more frequently.",
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   {
      CORE_NAME "_blargg_ntsc_filter",
      "Blargg NTSC Filter",
      "Apply a video filter to mimic various NTSC TV signals.",
      {
         { "disabled",   NULL },
         { "monochrome", "Monochrome" },
         { "composite",  "Composite" },
         { "svideo",     "S-Video" },
         { "rgb",        "RGB" },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      CORE_NAME "_lcd_filter",
      "LCD Ghosting Filter",
      "Apply an image 'ghosting' filter to mimic the display characteristics of the Game Gear and 'Genesis Nomad' LCD panels.",
      {
         { "disabled", NULL },
         { "enabled",  NULL },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      CORE_NAME "_overscan",
      "Borders",
      "Enable this to display the overscan regions at the top/bottom and/or left/right of the screen. These would normally be hidden by the bezel around the edge of a standard-definition television.",
      {
         { "disabled",   NULL },
         { "top/bottom", "Top/Bottom" },
         { "left/right", "Left/Right" },
         { "full",       "Full" },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      CORE_NAME "_gg_extra",
      "Game Gear Extended Screen",
      "Forces Game Gear titles to run in 'SMS' mode, with an increased resolution of 256x192. May show additional content, but typically displays a border of corrupt/unwanted image data.",
      {
         { "disabled", NULL },
         { "enabled",  NULL },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      CORE_NAME "_left_border",
      "Hide Master System Left Border",
      "Cuts off 8 pixels from both the left and right side of the screen when running Master System games, thereby hiding the border seen on the left side of the screen",
      {
         { "disabled", NULL },
         { "enabled",  NULL },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      CORE_NAME "_h40_extra_columns",
      "Extra columns to draw in H40 for widescreen",
      "Set the amount of extra colums to draw for widescreen",
      {
         { "10",NULL },
         { "0", NULL },
		 { "2", NULL },
         { "4", NULL },
		 { "6", NULL },
         { "8", NULL },
		 { "12", NULL },
         { "14", NULL },
		 { "16", NULL },
         { "18", NULL },
		 { "20", NULL },
         { "22", NULL },
		 { "24", NULL },
         { NULL, NULL },
      },
      "0"
   },
   {
      CORE_NAME "_vdp_fix_dma_boundary_bug",
      "Fix VDP DMA boundary bug",
      "Enable this to fix the VDP DMA boundary bug",
      {
         { "disabled", NULL },
         { "enabled",  NULL },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      CORE_NAME "_aspect_ratio",
      "Core-Provided Aspect Ratio",
      "Choose the preferred content aspect ratio. This will only apply when RetroArch's aspect ratio is set to 'Core provided' in the Video settings.",
      {
         { "auto",     "Auto" },
         { "NTSC PAR", NULL },
         { "PAL PAR",  NULL },
      },
      "auto"
   },
   {
      CORE_NAME "_render",
      "Interlaced Mode 2 Output",
      "Interlaced Mode 2 allows the Genesis to output a double height (high resolution) 320x448 image by drawing alternate scanlines each frame (this is used by 'Sonic the Hedgehog 2' and 'Combat Cars' multiplayer modes). 'Double Field' mimics original hardware, producing a sharp image with flickering/interlacing artefacts. 'Single Field' apples a de-interlacing filter, which stabilises the image but causes mild blurring.",
      {
         { "single field", "Single Field" },
         { "double field", "Double Field" },
         { NULL, NULL },
      },
      "single field"
   },
   {
      CORE_NAME "_gun_cursor",
      "Show Light Gun Crosshair",
      "Display light gun crosshairs when using the 'MD Menacer', 'MD Justifiers' and 'MS Light Phaser' input device types.",
      {
         { "disabled", NULL },
         { "enabled",  NULL },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      CORE_NAME "_gun_input",
      "Light Gun Input",
      "Use a mouse-controlled 'Light Gun' or 'Touchscreen' input.",
      {
         { "lightgun",    "Light Gun" },
         { "touchscreen", "Touchscreen" },
         { NULL, NULL },
      },
      "lightgun"
   },
   {
      CORE_NAME "_invert_mouse",
      "Invert Mouse Y-Axis",
      "Inverts the Y-axis of the 'MD Mouse' input device type.",
      {
         { "disabled", NULL },
         { "enabled",  NULL },
         { NULL, NULL },
      },
      "disabled"
   },
#ifdef HAVE_OVERCLOCK
   {
      CORE_NAME "_overclock",
      "CPU Speed",
      "Overclock the emulated CPU. Can reduce slowdown, but may cause glitches.",
      {
         { "100%", NULL },
         { "125%", NULL },
         { "150%", NULL },
         { "175%", NULL },
         { "200%", NULL },
         { NULL, NULL },
      },
      "100%"
   },
#endif
   {
      CORE_NAME "_no_sprite_limit",
      "Remove Per-Line Sprite Limit",
      "Removes the 8 (Master System) or 20 (Genesis) sprite-per-scanline hardware limit. This reduces flickering but can cause visual glitches, as some games exploit the hardware limit to generate special effects.",
      {
         { "disabled", NULL },
         { "enabled",  NULL },
         { NULL, NULL },
      },
      "disabled"
   },
#ifdef USE_PER_SOUND_CHANNELS_CONFIG
   {
      CORE_NAME "_show_advanced_audio_settings",
      "Show Advanced Audio Volume Settings (Reopen menu)",
      "Enable configuration of low-level audio channel parameters. NOTE: Quick Menu must be toggled for this setting to take effect.",
      {
         { "enabled",  NULL },
         { "disabled", NULL },
         { NULL, NULL},
      },
      "disabled"
   },
   {
      CORE_NAME "_psg_channel_0_volume",
      "PSG Tone Channel 0 Volume %",
      "Reduce the volume of the PSG Tone Channel 0.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_psg_channel_1_volume",
      "PSG Tone Channel 1 Volume %",
      "Reduce the volume of the PSG Tone Channel 1.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_psg_channel_2_volume",
      "PSG Tone Channel 2 Volume %",
      "Reduce the volume of the PSG Tone Channel 2.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_psg_channel_3_volume",
      "PSG Noise Channel 3 Volume %",
      "Reduce the volume of the PSG Noise Channel 3.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_md_channel_0_volume",
      "Mega Drive / Genesis FM Channel 0 Volume %",
      "Reduce the volume of the Mega Drive / Genesis FM Channel 0. Only works with MAME FM emulators.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_md_channel_1_volume",
      "Mega Drive / Genesis FM Channel 1 Volume %",
      "Reduce the volume of the Mega Drive / Genesis FM Channel 1. Only works with MAME FM emulators.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_md_channel_2_volume",
      "Mega Drive / Genesis FM Channel 2 Volume %",
      "Reduce the volume of the Mega Drive / Genesis FM Channel 2. Only works with MAME FM emulators.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_md_channel_3_volume",
      "Mega Drive / Genesis FM Channel 3 Volume %",
      "Reduce the volume of the Mega Drive / Genesis FM Channel 3. Only works with MAME FM emulators.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_md_channel_4_volume",
      "Mega Drive / Genesis FM Channel 4 Volume %",
      "Reduce the volume of the Mega Drive / Genesis FM Channel 4. Only works with MAME FM emulators.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_md_channel_5_volume",
      "Mega Drive / Genesis FM Channel 5 Volume %",
      "Reduce the volume of the Mega Drive / Genesis FM Channel 5. Only works with MAME FM emulators.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_sms_fm_channel_0_volume",
      "Master System FM (YM2413) Channel 0 Volume %",
      "Reduce the volume of the Master System FM Channel 0.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_sms_fm_channel_1_volume",
      "Master System FM (YM2413) Channel 1 Volume %",
      "Reduce the volume of the Master System FM Channel 1.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_sms_fm_channel_2_volume",
      "Master System FM (YM2413) Channel 2 Volume %",
      "Reduce the volume of the Master System FM Channel 2.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_sms_fm_channel_3_volume",
      "Master System FM (YM2413) Channel 3 Volume %",
      "Reduce the volume of the Master System FM Channel 3.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_sms_fm_channel_4_volume",
      "Master System FM (YM2413) Channel 4 Volume %",
      "Reduce the volume of the Master System FM Channel 4.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_sms_fm_channel_5_volume",
      "Master System FM (YM2413) Channel 5 Volume %",
      "Reduce the volume of the Master System FM Channel 5.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_sms_fm_channel_6_volume",
      "Master System FM (YM2413) Channel 6 Volume %",
      "Reduce the volume of the Master System FM Channel 6.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_sms_fm_channel_7_volume",
      "Master System FM (YM2413) Channel 7 Volume %",
      "Reduce the volume of the Master System FM Channel 7.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
   {
      CORE_NAME "_sms_fm_channel_8_volume",
      "Master System FM (YM2413) Channel 8 Volume %",
      "Reduce the volume of the Master System FM Channel 8.",
      {
         { "0",   NULL },
         { "10",  NULL },
         { "20",  NULL },
         { "30",  NULL },
         { "40",  NULL },
         { "50",  NULL },
         { "60",  NULL },
         { "70",  NULL },
         { "80",  NULL },
         { "90",  NULL },
         { "100", NULL },
         { NULL, NULL },
      },
      "100"
   },
#endif
   { NULL, NULL, NULL, {{0}}, NULL },
};

/*
 ********************************
 * Language Mapping
 ********************************
*/

#ifndef HAVE_NO_LANGEXTRA
struct retro_core_option_definition *option_defs_intl[RETRO_LANGUAGE_LAST] = {
   option_defs_us, /* RETRO_LANGUAGE_ENGLISH */
   NULL,           /* RETRO_LANGUAGE_JAPANESE */
   NULL,           /* RETRO_LANGUAGE_FRENCH */
   NULL,           /* RETRO_LANGUAGE_SPANISH */
   NULL,           /* RETRO_LANGUAGE_GERMAN */
   NULL,           /* RETRO_LANGUAGE_ITALIAN */
   NULL,           /* RETRO_LANGUAGE_DUTCH */
   option_defs_pt_br, /* RETRO_LANGUAGE_PORTUGUESE_BRAZIL */
   NULL,           /* RETRO_LANGUAGE_PORTUGUESE_PORTUGAL */
   NULL,           /* RETRO_LANGUAGE_RUSSIAN */
   NULL,           /* RETRO_LANGUAGE_KOREAN */
   NULL,           /* RETRO_LANGUAGE_CHINESE_TRADITIONAL */
   NULL,           /* RETRO_LANGUAGE_CHINESE_SIMPLIFIED */
   NULL,           /* RETRO_LANGUAGE_ESPERANTO */
   NULL,           /* RETRO_LANGUAGE_POLISH */
   NULL,           /* RETRO_LANGUAGE_VIETNAMESE */
   NULL,           /* RETRO_LANGUAGE_ARABIC */
   NULL,           /* RETRO_LANGUAGE_GREEK */
   option_defs_tr, /* RETRO_LANGUAGE_TURKISH */
};
#endif

/*
 ********************************
 * Functions
 ********************************
*/

/* Handles configuration/setting of core options.
 * Should be called as early as possible - ideally inside
 * retro_set_environment(), and no later than retro_load_game()
 * > We place the function body in the header to avoid the
 *   necessity of adding more .c files (i.e. want this to
 *   be as painless as possible for core devs)
 */

INLINE void libretro_set_core_options(retro_environment_t environ_cb)
{
   unsigned version = 0;

   if (!environ_cb)
      return;

   if (environ_cb(RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION, &version) && (version >= 1))
   {
#ifndef HAVE_NO_LANGEXTRA
      struct retro_core_options_intl core_options_intl;
      unsigned language = 0;

      core_options_intl.us    = option_defs_us;
      core_options_intl.local = NULL;

      if (environ_cb(RETRO_ENVIRONMENT_GET_LANGUAGE, &language) &&
          (language < RETRO_LANGUAGE_LAST) && (language != RETRO_LANGUAGE_ENGLISH))
         core_options_intl.local = option_defs_intl[language];

      environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS_INTL, &core_options_intl);
#else
      environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS, &option_defs_us);
#endif
   }
   else
   {
      size_t i;
      size_t num_options               = 0;
      struct retro_variable *variables = NULL;
      char **values_buf                = NULL;

      /* Determine number of options */
      while (true)
      {
         if (option_defs_us[num_options].key)
            num_options++;
         else
            break;
      }

      /* Allocate arrays */
      variables  = (struct retro_variable *)calloc(num_options + 1, sizeof(struct retro_variable));
      values_buf = (char **)calloc(num_options, sizeof(char *));

      if (!variables || !values_buf)
         goto error;

      /* Copy parameters from option_defs_us array */
      for (i = 0; i < num_options; i++)
      {
         const char *key                        = option_defs_us[i].key;
         const char *desc                       = option_defs_us[i].desc;
         const char *default_value              = option_defs_us[i].default_value;
         struct retro_core_option_value *values = option_defs_us[i].values;
         size_t buf_len                         = 3;
         size_t default_index                   = 0;

         values_buf[i] = NULL;

         if (desc)
         {
            size_t num_values = 0;

            /* Determine number of values */
            while (true)
            {
               if (values[num_values].value)
               {
                  /* Check if this is the default value */
                  if (default_value)
                     if (strcmp(values[num_values].value, default_value) == 0)
                        default_index = num_values;

                  buf_len += strlen(values[num_values].value);
                  num_values++;
               }
               else
                  break;
            }

            /* Build values string */
            if (num_values > 0)
            {
               size_t j;

               buf_len += num_values - 1;
               buf_len += strlen(desc);

               values_buf[i] = (char *)calloc(buf_len, sizeof(char));
               if (!values_buf[i])
                  goto error;

               strcpy(values_buf[i], desc);
               strcat(values_buf[i], "; ");

               /* Default value goes first */
               strcat(values_buf[i], values[default_index].value);

               /* Add remaining values */
               for (j = 0; j < num_values; j++)
               {
                  if (j != default_index)
                  {
                     strcat(values_buf[i], "|");
                     strcat(values_buf[i], values[j].value);
                  }
               }
            }
         }

         variables[i].key   = key;
         variables[i].value = values_buf[i];
      }

      /* Set variables */
      environ_cb(RETRO_ENVIRONMENT_SET_VARIABLES, variables);

error:

      /* Clean up */
      if (values_buf)
      {
         for (i = 0; i < num_options; i++)
         {
            if (values_buf[i])
            {
               free(values_buf[i]);
               values_buf[i] = NULL;
            }
         }

         free(values_buf);
         values_buf = NULL;
      }

      if (variables)
      {
         free(variables);
         variables = NULL;
      }
   }
}

#ifdef __cplusplus
}
#endif

#endif