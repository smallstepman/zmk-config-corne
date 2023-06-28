#include <behaviors.dtsi>
#include <dt-bindings/zmk/keys.h>

#include "../zmk-nodefree-config/helper.h"
#include "../zmk-nodefree-config/keypos_def/keypos_36keys.h"
#include "../zmk-nodefree-config/international_chars/german.dtsi"

/* layer and key shortcuts */

#define ___ &trans

#define DEF 0  // layer shortcuts, must match order in which they are defined below
#define NAV 1
#define NUM 2
#define GER 3

/* custom behaviors */

// homerow mods
ZMK_BEHAVIOR(hrm, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <280>;
    quick-tap-ms = <125>;
    global-quick-tap;
    bindings = <&kp>, <&kp>;
)

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
#undef COMBO_TERM
#define COMBO_TERM 40  // timeout of 40ms (default is 30ms if omitted)
ZMK_COMBO(combo_sleep,  &win_sleep, RT3 RT4, NAV)  // custom sleep macro, only active on NAV layer
ZMK_COMBO(combo_copy,   &kp LC(C),  LB2 LB3, ALL)  // Ctrl + C, active on all layers
ZMK_COMBO(combo_paste,  &kp LC(V),  LB1 LB2, ALL)  // Ctrl + V, active on all layers

/* keymap */

ZMK_LAYER(default_layer,
      // ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮ ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮
          &kp TAB     &kp Q       &kp W       &kp E       &kp R       &kp T         &kp Y       &kp U       &kp I       &kp O       &kp P       &kp ESC
      // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
          &kp LCTRL   &kp A       &kp S       &kp D       &kp F       &kp G         &kp H       &kp J       &kp K       &kp L       &kp SEMI    &hrm LGUI O
      // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
          &kp LSHFT   &kp Z       &kp X       &kp C       &kp V       &kp B         &kp N       &kp M       &kp COMMA   &kp DOT     &kp FSLH    &kp RSHFT 
      // ╰───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ┤───────────┼───────────┼───────────┼───────────┼───────────┼───────────╯
                                              &kp LGUI    &ss_cw       &kp RET       &lt NAV SPACE &bs_del_num ___
      //                                     ╰───────────┴───────────┴───────────╯ ╰───────────┴───────────┴───────────╯
          )

ZMK_LAYER(nav_layer,
      // ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮ ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮
          ___         ___         ___         ___         ___         ___           &kp PG_UP   &kp HOME    &kp UP      &kp END     &kp INS     ___
      // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
          ___         &sk LGUI    &sk LALT    &sk LCTRL   &sk LSHFT   ___           &kp PG_DN   &kp LEFT    &kp DOWN    &kp RIGHT   &kp DEL     ___
      // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
          ___         ___         ___         ___         ___         ___           ___         &kp LC(X)   &kp LC(INS) &kp LS(INS) ___         ___
      // ╰───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ┤───────────┼───────────┼───────────┼───────────┼───────────┼───────────╯
                                              ___         ___         ___           ___         ___         ___
      //                                     ╰───────────┴───────────┴───────────╯ ╰───────────┴───────────┴───────────╯
          )

ZMK_LAYER(num_layer,
      // ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮ ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮
          ___         &kp ESC     &kp N7      &kp N8      &kp N9      &kp STAR      ___         ___         ___         ___         ___         ___
      // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
          ___         &kp TAB     &kp N4      &kp N5      &kp N6      &kp PLUS      ___         &sk RSHFT   &sk LCTRL   &sk LALT    &sk LGUI    ___
      // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
          ___         &kp RET     &kp N1      &kp N2      &kp N3      &kp FSLH      ___         ___         ___         ___         ___         ___
      // ╰───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ┤───────────┼───────────┼───────────┼───────────┼───────────┼───────────╯
                                              &kp DOT     &kp N0      &kp MINUS     ___         ___         ___
      //                                     ╰───────────┴───────────┴───────────╯ ╰───────────┴───────────┴───────────╯
          )
ZMK_LAYER(german_layer,
      // ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮ ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮
          ___         ___         ___         ___         ___         ___           ___         &de_ue      ___         &de_oe      ___         ___
      // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
          ___         &de_ae      &de_eszett  ___         ___         ___           ___         ___         ___         ___         ___         ___
      // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
          ___         ___         ___         ___         ___         ___           ___         ___         ___         ___         ___         ___
      // ╰───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ┤───────────┼───────────┼───────────┼───────────┼───────────┼───────────╯
                                              ___         ___         ___           ___         ___         ___
      //                                     ╰───────────┴───────────┴───────────╯ ╰───────────┴───────────┴───────────╯
          )
