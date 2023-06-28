#include <behaviors.dtsi>
#include <dt-bindings/zmk/keys.h>
#include <dt-bindings/zmk/bt.h>

#include "../zmk-nodefree-config/helper.h"
#include "../zmk-nodefree-config/keypos_def/keypos_42keys.h"
#include "../zmk-nodefree-config/international_chars/german.dtsi"

/* layer and key shortcuts */
#define XXX &none
#define ___ &trans

#define DEF 0  // layer shortcuts, must match order in which they are defined below
#define NAV 1
#define NUM 2
#define GER 3
#define SYS 4
#define MOU 5


#include "mouse.dtsi"

#define QUICK_TAP_MS 175

&sk {  // sticky-key config
    release-after-ms = <900>;  // release after 0.6s
    quick-release;             // no double capitalization when rolling keys
};

&sl {  // sticky-layer config
    ignore-modifiers;          // allow chording sticky mods & layers
};

&lt {  // layer-tap config
    flavor = "balanced";
    tapping-term-ms = <200>;
    quick-tap-ms = <QUICK_TAP_MS>;
};



#define KEYS_L LT0 LT1 LT2 LT3 LT4 LM0 LM1 LM2 LM3 LM4 LB0 LB1 LB2 LB3 LB4  // left hand
#define KEYS_R RT0 RT1 RT2 RT3 RT4 RM0 RM1 RM2 RM3 RM4 RB0 RB1 RB2 RB3 RB4  // right hand
#define THUMBS LH2 LH1 LH0 RH0 RH1 RH2                                      // thumbs

#define MAKE_HRM(NAME, HOLD, TAP, TRIGGER_POS) \
    ZMK_BEHAVIOR(NAME, hold_tap, \
        flavor = "balanced"; \
        tapping-term-ms = <280>; \
        quick-tap-ms = <QUICK_TAP_MS>; \
        global-quick-tap-ms = <150>; \
        bindings = <HOLD>, <TAP>; \
        hold-trigger-key-positions = <TRIGGER_POS>; \
        hold-trigger-on-release; \
    )
MAKE_HRM(hml, &kp, &kp, KEYS_R THUMBS)  // left-hand HRMs
MAKE_HRM(hmr, &kp, &kp, KEYS_L THUMBS)  // right-hand HRMs

MAKE_HRM(hml_repeat, &kp, &key_repeat, KEYS_R THUMBS)  // used for HRM-combo
MAKE_HRM(hmr_lpar_lt, &kp, &lpar_lt, KEYS_L THUMBS)    // "    "   "   "
MAKE_HRM(hmr_rpar_gt, &kp, &rpar_gt, KEYS_L THUMBS)    // "    "   "   "


// tap: left-parenthesis | shft + tap: less-than
ZMK_BEHAVIOR(lpar_lt, mod_morph,
    bindings = <&kp LPAR>, <&kp LT>;
    mods = <(MOD_LSFT|MOD_RSFT)>;
)

// tap: right-parenthesis | shft + tap: greater-than
ZMK_BEHAVIOR(rpar_gt, mod_morph,
    bindings = <&kp RPAR>, <&kp GT>;
    mods = <(MOD_LSFT|MOD_RSFT)>;
)

         /////// old

// tap: sticky shift | double tap: capsword
ZMK_BEHAVIOR(ss_cw, tap_dance,
    tapping-term-ms = <200>;
    bindings = <&sk LSHFT>, <&caps_word>;
)

// tap: backspace | shift + tap: delete | hold: num layer
ZMK_BEHAVIOR(bs_del_num, mod_morph,
    bindings = <&lt NUM BSPC>, <&kp DEL>;
    mods = <(MOD_LSFT|MOD_RSFT)>;
)

// windows sleep macro
ZMK_BEHAVIOR(win_sleep, macro,
    wait-ms = <100>;
    tap-ms = <5>;
    bindings = <&kp LG(X) &kp U &kp S>;
)

// euro sign
ZMK_UNICODE_SINGLE(euro_sign, N2, N0, A, C)  // €

// replace a/o/u/s with German umlauts when NAV and NUM are held jointly
ZMK_CONDITIONAL_LAYER(NAV NUM, GER)

// combos
ZMK_COMBO(combo_sleep,  &win_sleep, RT3 RT4, NAV)  // custom sleep macro, only active on NAV layer
ZMK_COMBO(combo_copy,   &kp LC(C),  LB2 LB3, ALL)  // Ctrl + C, active on all layers
ZMK_COMBO(combo_paste,  &kp LC(V),  LB1 LB2, ALL)  // Ctrl + V, active on all layers

/* keymap */

ZMK_LAYER(default_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          &kp ESC        &kp Q          &kp W          &kp E          &kp R          &kp T            &kp Y          &kp U          &kp I          &kp O          &kp P          ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          &mo SYS        &hml LGUI A    &hml LALT S    &hml LCTRL D   &hml LSHFT F   &kp G            &kp H          &hmr RSHFT J   &hmr LCTRL K   &hmr LALT L    &hmr LGUI SEMI ___ 
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          &kp LSHFT      &kp Z          &kp X          &kp C          &kp V          &kp B            &kp N          &kp M          &kp COMMA      &kp DOT        &kp FSLH       &kp RSHFT 
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ┤──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                                       &mo NAV        &kp TAB        &kp SPACE        &kp RET        &kp BSPC       &bs_del_num
      //                                              ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )

ZMK_LAYER(nav_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          ___            ___            ___            ___            ___            ___              &kp PG_UP      &kp HOME       &kp UP         &kp END        &kp INS        ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            &sk LGUI       &sk LALT       &sk LCTRL      &sk LSHFT      ___              &kp PG_DN      &kp LEFT       &kp DOWN       &kp RIGHT      &kp DEL        ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            ___            ___            ___            ___            ___              ___            &kp LC(X)      &kp LC(INS)    &kp LS(INS)    ___            ___
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ┤──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                              ___            ___            ___              ___            ___            ___
      //                                     ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )

ZMK_LAYER(num_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          ___            &kp ESC        &kp N7         &kp N8         &kp N9         &kp STAR         ___            ___            ___            ___            ___            ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            &kp TAB        &kp N4         &kp N5         &kp N6         &kp PLUS         ___            &sk RSHFT      &sk LCTRL      &sk LALT       &sk LGUI       ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            &kp RET        &kp N1         &kp N2         &kp N3         &kp FSLH         ___            ___            ___            ___            ___            ___
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ┤──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                              &kp DOT        &kp N0         &kp MINUS        ___            ___            ___
      //                                     ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )

ZMK_LAYER(german_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          ___            ___            ___            ___            ___            ___              ___            &de_ue         ___            &de_oe         ___            ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            &de_ae         &de_eszett     ___            ___            ___              ___            ___            ___            ___            ___            ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            ___            ___            ___            ___            ___              ___            ___            ___            ___            ___            ___
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ┤──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                              ___            ___            ___              ___            ___            ___
      //                                     ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )

ZMK_LAYER(system_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          &bt BT_CLR     &bt BT_SEL 0   &bt BT_SEL 1   &bt BT_SEL 2   &bt BT_SEL 3   &bt BT_SEL 4     ___            ___            ___            ___            ___            ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            ___            ___            ___            ___            &bootloader      &bootloader    ___            ___            ___            ___            ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            ___            ___            ___            ___            &sys_reset       &sys_reset     ___            ___            ___            ___            ___
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ┤──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                              ___            ___            ___              ___            ___            ___
      //                                     ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )

ZMK_LAYER(mouse_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          ___            ___            ___            ___            ___            ___              ___            U_WH_D         U_MS_U         U_WH_U         ___            ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            ___            ___            ___            ___            ___              ___            U_MS_L         U_MS_D         U_MS_R         ___            ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            ___            ___            ___            ___            ___              ___            ___            ___            ___            ___            ___
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ┤──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                              ___            ___            ___              U_BTN2         U_BTN1         ___
      //                                     ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )
