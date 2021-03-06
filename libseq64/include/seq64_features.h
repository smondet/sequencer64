#ifndef SEQ64_FEATURES_H
#define SEQ64_FEATURES_H

/*
 *  This file is part of seq24/sequencer64.
 *
 *  seq24 is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  seq24 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with seq24; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * \file          seq64_features.h
 *
 *    This module summarizes or defines all of the configure and build-time
 *    options available for Sequencer64.
 *
 * \library       sequencer64 application
 * \author        Chris Ahlstrom
 * \date          2016-08-19
 * \updates       2018-11-03
 * \license       GNU GPLv2 or above
 *
 *    Some options (the "USE_xxx" options) specify experimental and
 *    unimplemented features.  Some options (the "SEQ64_xxx" options)
 *    might be experimental, or not, but are definitely supported, if defined,
 *    and may become configure-time options.
 *
 *    Some options are available (or can be disabled) by running the
 *    "configure" script generated using the configure.ac file.  These
 *    options are things that a normal user or a seq24 aficianado might want to
 *    disable.  They are defined as desired, in the auto-generated
 *    seq64-config.h file in the top-level "include" directory.
 *
 *    The rest of the options can be modified only by editing the source code
 *    (soon to be this file) to enable or disable features.  These options are
 *    those that we feel more strongly about.
 *
 *    Currently, we've tested all the experimental options to the extent of
 *    building them successfully.  However, enabling them is currently
 *    TEMPORARY; we want to build with them all disabled, and enable them
 *    one-by-one in a controlled, tested manner.
 */

#include <string>

#include "seq64-config.h"

/*
 *  We need to disable some features not yet available in the Qt 5 user
 *  interface.
 */

#ifdef SEQ64_QTMIDI_SUPPORT
#define SEQ64_QT5_USER_INTERFACE
#endif

/**
 *  Kepler34 has a drum edit mode that we are still exploring and adding,
 *  marked by the following macro to keep it out of the way until the feature
 *  is ready for prime time.  Currently builds but is incomplete and not
 *  tested.
 */

#undef USE_SEQUENCE_EDIT_MODE

/**
 *  Kepler34 has a feature for coloring sequence patterns.  However, it
 *  forces every MIDI file to carry 1024 instances of color information.
 *  Compiles, but don't enable until we decide it's worth storing an extra
 *  1024 bytes in the MIDI file.  Instead, see SEQ64_SHOW_COLOR_PALETTE.
 */

#undef USE_KEPLER34_SEQUENCE_COLOR

/**
 *  A better way to implement the Kepler34 sequence-color feature.  Here,
 *  each sequence that has color has an optional SeqSpec for pattern color.
 */

#define SEQ64_SHOW_COLOR_PALETTE

/**
 *  Kepler34 has a song-recording mode that we are still exploring and adding,
 *  marked by the following macro to keep it out of the way until the feature
 *  is ready for prime time.  This feature has been requested by some users of
 *  Sequencer64.  Currently builds but is not fully tested.
 */

#define SEQ64_SONG_RECORDING

/**
 *  Kepler34 allows the user to select (and move) more than one sequence in
 *  the Song Editor.  Currently builds but is incomplete and not tested.
 *  Currently broken.  Still refactoring!
 *
 *  This is our version, which currently supports only the "Shift-select"
 *  option, where the user holds the shift key while clicking triggers to
 *  select more than one.  It now seems a bit off-base, so we're disabling
 *  this feature for now.  A trigger selection can only be completely
 *  specified by it sequence number and the start tick of the trigger.
 */

#ifdef SEQ64_QTMIDI_SUPPORT
#define SEQ64_SONG_BOX_SELECT
#else
#undef  SEQ64_SONG_BOX_SELECT           /* not ready in Gtkmm support       */
#endif

/**
 *  We're in the middle of adding playlist support.  Some might not like the
 *  overhead, so we're making it a compile-time header option.  However, the
 *  playlist class will still be compiled, but hopefully not linked.
 *
 *  Making this option permanent.  It is useful, and for seq64cli, mandatory.
 *  Removed this macro from all modules.
 *
 *      #define SEQ64_USE_MIDI_PLAYLIST
 */

/**
 *  Currently, many macros are undefined as tentative or experimental.
 */

/**
 *  Adds a seqedit menu option to expand a pattern/sequence by doubling it, or
 *  to compress a pattern/sequence by halving it.  These operations are
 *  accomplished by the sequence::multiply_patten() function.
 */

#undef USE_STAZED_COMPANDING

/**
 *  Adds: (1) skipping some bars in drawing the grid in perftime, to allow for
 *  in-tight zoom levels; (2) setting and grabbing the focus in seqedit if the
 *  sequence has been given a name (and thus presumably been edited).
 */

#undef USE_STAZED_EXTRAS

/**
 *  If defined, adds some extra snap values to the perfedit snap menu.
 *  We suspect there's a more elegant way to handle getting snap to handle
 *  varying zoom values and things like triplets, but we want to make sure
 *  this code at least compiles.
 */

#undef USE_STAZED_EXTRA_SNAPS

/**
 *  Adds more SYSEX processing, plus the ability to read SYSEX information
 *  from a file.
 */

#undef USE_SYSEX_PROCESSING            /* disabled in Seq24 as well        */

/**
 *  Adds a button to disable the main menu in the main window.  Adds a button
 *  to set the Song (versus Live) mode from the main menu in the main window.
 *  There is also an other, less public macro, SEQ64_MENU_BUTTON_PIXMAPS,
 *  that selects between using pixmaps to represent the "Song"/"Live",
 *  "Muting", and "Menu" buttons in the mainwnd window, or the text
 *  equivalents.  That value can be found in the seq_gtkmm2/include/mainwnd.hpp
 *  file, should one want to use text instead.  Now permanent.
 *
 *      #ifndef SEQ64_QT5_USER_INTERFACE // include/qt/portmidi/seq64-config.h
 *      #define SEQ64_STAZED_MENU_BUTTONS
 *      #endif
 */

/**
 *  If defined, this macro adds a small button next to the BPM setting that
 *  can be used to calculate a tempo based on the user's periodic clicks.
 *  (Later, a shortcut key will be added).  Inspired by a request from user
 *  alejg.
 *
 *  No longer needed; this feature is now permanent.
 *
 * #define SEQ64_MAINWND_TAP_BUTTON
 */

/**
 *  In the perform object, replaces a direct call to sequence::stream_event()
 *  with a call to mastermidibus::dump_midi_input(), which then is supposed to
 *  allocate the event to the sequence that has a matching channel.
 *  Unlike in Seq32, however, this is currently a member option in the sequence
 *  class.  We will want to make it a run-time option and then remove this
 *  macro here.  Done.  See the rc_settings::filter_by_channel() option.
 *
 * #define USE_STAZED_MIDI_DUMP
 */

/**
 *  Adds the ability to select odd/even notes in seqedit.
 */

#undef USE_STAZED_ODD_EVEN_SELECTION

/**
 *  Not yet defined.
 */

#undef USE_STAZED_SELECTION_EXTENSIONS

/**
 *  Not yet defined.
 */

#undef USE_STAZED_PLAYING_CONTROL

/**
 *  Not yet defined.
 */

#undef USE_STAZED_RANDOMIZE_SUPPORT

/**
 *  Not yet defined.
 */

#undef USE_STAZED_SEQDATA_EXTENSIONS

/**
 *  Not yet defined.
 */

#undef USE_STAZED_SHIFT_SUPPORT

/**
 *  Stazed implementation of auto-scroll.
 */

#undef USE_STAZED_PERF_AUTO_SCROLL

/*
 * To recapitulate, all the options above are experimental and may not
 * even be in progress.
 */

/**
 * Configure-time options.
 *
 *    - SEQ64_HAVE_LIBASOUND
 *    - SEQ64_HIGHLIGHT_EMPTY_SEQS
 *    - SEQ64_JACK_SESSION
 *    - SEQ64_JACK_SUPPORT
 *    - SEQ64_LASH_SUPPORT
 *    - SEQ64_MULTI_MAINWID
 *      Provides support for up to a 3 x 2 array of mainwids.  Now a configure
 *      option.
 */

/*
 * Edit-time (permanent) options.
 */

/**
 *  EXPERIMENTAL.  Not yet working, removed.  A very tough problem.  The idea
 *  is to go into an auto-screen-set mode via a menu entry, where the current
 *  screen-set is queued for muting, while the next selected screen-set is
 *  queued for unmuting.
 *
 *  #undef  SEQ64_USE_AUTO_SCREENSET_QUEUE
 */

/**
 *  Try to highlight the selected pattern using black-on-cyan
 *  coloring, in addition to the red progress bar marking that already exists.
 *  Moved from seqmenu.  Seems to work pretty well now.
 */

#ifdef SEQ64_QTMIDI_SUPPORT
#undef SEQ64_EDIT_SEQUENCE_HIGHLIGHT    /* not ready in Qt 5 support        */
#else
#define SEQ64_EDIT_SEQUENCE_HIGHLIGHT
#endif

/**
 *  This special value of zoom sets the zoom according to a power of two
 *  related to the PPQN value of the song.
 */

#define SEQ64_USE_ZOOM_POWER_OF_2       0

/*
 * Others
 */

/**
 *  This provides a build option for having the pattern editor window scroll
 *  to keep of with the progress bar, for sequences that are longer than the
 *  measure or two that a pattern window will show.
 *
 *  We thought about making this a configure option or a run-time option, but
 *  this kind of scrolling is a universal convention of MIDI sequencers.  If
 *  you really don't like this feature, let me know, and I will make it a
 *  configure option.  We could also disable it it "legacy" mode, which also
 *  disables a lot of other features.
 *
 *  Now a permanent option.  Can be disabled for each individual edit or
 *  performance window.
 *
 * #define SEQ64_FOLLOW_PROGRESS_BAR
 */

/**
 *  An option we've preserved from Seq24, but have disabled until we find a
 *  need for it, is to tally some "statistics" about recording and playback.
 */

#undef  SEQ64_STATISTICS_SUPPORT

/**
 *  A color option.
 */

#define SEQ64_USE_BLACK_SELECTION_BOX

/**
 * This macro indicates an experimental feature where we are trying to see
 * if using std::multimap as an event-container has any benefits over
 * using std::list.  Define this macro to use the multimap.  So far, we
 * recommend using it.  In debug mode, the b4uacuse MIDI files take about 8
 * seconds (!) to load using the list, but barely any time to load using the
 * multimap.  It turns out the multimap does have issues; one must be careful
 * dealing with insertions since multiple events with the same keys can be
 * load.  This caused an issue with copy/paste leaving unlinked notes that
 * would either play forever or not play at all.  A good fix was provided by
 * user 0rel.
 *
 * We have another issue.  On a low-end, single-core, 32-bit laptop, the
 * new b4uacuse-stress.midi file (1.5 Mb!) loads in a couple seconds with the
 * map implementation, but takes 13 minutes (!) to load with the list
 * implementation.  But it can't play properly from the map; it can play
 * somewhat properly from the list.  We've added code to sort the event list
 * after the fact when loading the file, which speeds things up.  But, as
 * the contrib/notes/ev*.png files show, the events are drawn funny in the
 * pattern slot.  They play fine, though.
 *
 * What we finally did was use the faster list method, but only sort the list
 * after adding every event to it.
 */

#undef SEQ64_USE_EVENT_MAP              /* map seems to work well! But...   */

/**
 *  Enables some mute-group patches contributed by a Sequencer64 user.
 */

#define SEQ64_USE_TDEAGAN_CODE

/*
 * #define SEQ64_USE_DEBUG_OUTPUT (normally disabled)
 */

#endif      // SEQ64_FEATURES_H

/*
 * This is the main namespace of Sequencer64.  Do not attempt to
 * Doxygenate the documentation here; it breaks Doxygen.
 */

namespace seq64
{

/*
 * Global (free) functions.
 */

extern void set_app_name (const std::string & aname);
extern void set_client_name (const std::string & cname);
extern const std::string & seq_app_name ();
extern const std::string & seq_client_name ();
extern const std::string & seq_version ();
extern const std::string & seq_version_text ();
extern const std::string & seq_app_tag ();

}           // namespace seq64

/*
 * seq64_features.h
 *
 * vim: sw=4 ts=4 wm=4 et ft=cpp
 */

