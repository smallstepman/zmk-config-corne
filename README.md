![keymap](./keymap-drawer/corne.svg)

# Regenerate keymap visualization

``` shell
keymap parse -c 10 -z config/corne.keymap | keymap -c keymap-drawer/config.yaml draw - > keymap-drawer/corne.svg 
```
