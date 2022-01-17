Driver for Texas Instruments TSC2046 Touch Controller - Arduino Framework
It should also work for Chinese clones of the 2046

I spent quite some effort trying to detect Z-Axis / Pressure in a reliable way. Even with the instructions from the datasheet/application notes, this was not really working well over the full aera of the display, so I removed it again.
This means the touchScreen driver can only detect a press/release, and so this needs to be debounced properly, otherwise when touching the touchScreen with a pressure around the threshold, it will generate several press/release events..

