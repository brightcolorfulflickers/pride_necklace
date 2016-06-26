# pride_necklace
A Neopixel necklace to celebrate LGBT pride.

![Rainbow Flag Necklace](https://github.com/brightcolorfulflickers/pride_necklace/blob/master/photos/necklace front on small.jpg)

## Overview
I made this necklace to celebrate LGBT pride month. It's based on [this Adafruit tutorial](https://learn.adafruit.com/gemma-hoop-earrings/overview), but I modified it heavily. It adds a button so that the user can cycle through different animations. Full instructions are below.

## Tools Required

I used a laser cutter, a 3d printer, and a soldering iron.

## Parts Used

Electronic parts:
- [Adafruit Gemma](https://www.adafruit.com/product/1222)
- [16 Neopixel Ring](https://www.adafruit.com/product/1463)
- [150 mAh battery](https://www.adafruit.com/product/1317)
- [Slim button](https://www.adafruit.com/products/1489)
- 10k resistor
- 26 AWG stranded wire

Other parts:
- E6000 adhesive
- Acrylic: [3/16" clear](http://www.mcmaster.com/#8560K163), [1/8" clear](http://www.mcmaster.com/#8560K239), [1/8" frosted](http://www.ebay.com/itm/272185258220)
- PLA filament
- [Glue-on pendant bail](https://www.etsy.com/transaction/1154709693)
- Chain of your choice - buy at any craft store

## Instructions

For the electronic part, mostly follow the Adafruit tutorial linked above. However, I made the following modifications.
- Solder the button between 3V and D0.
- Solder the resistor between D0 and D2.
- Be sure to solder to the 5V on the Neopixel ring right under the "Power 5V DC" label and the ground to the ground right under the "Ground" label.

Upload the code: pridenecklace.ino. This version has the rainbow flag, but you can modify this to make your own flags. I've included code for the bisexual and trans pride flags as well; see prideoutfit.ino. The main limitation is the low memory of the Gemma.

Laser cut the following parts:
- Cut "necklace back.svg" on the 1/8" clear acrylic.
- Cut "necklace front.svg" -- one copy of the circle on the 1/8" frosted acrylic, and two copies of the circle on the 3/16" clear acrylic.
These files were created in Inkscape. I simply used the dimensions provided by Adafruit, if you would like to re-create them.

3D print the 150 mAh battery case. I just did a "fast print" in Cura to generate my gcode.

Use the E6000 to glue the small round piece to the back of the Gemma. Glue the ring with cutouts for the solder joints to the back of the Neopixel ring. Allow that to set and dry overnight.

Next, glue the pendant bail to the acrylic on the back on the Neopixel ring. Be sure to line up the bail with the top pixel, which is between the Adafruit flower and the Data Input solder joint. Also glue the battery case to the back of the acrylic on the Gemma. Line up the top opening of the case with the flat top cutout of the acrylic.

Glue the two remaining clear acrylic circles together, and glue the frosted acrylic circle on top of that. Be sure to spread a thin, even layer of the glue. Be sure all three layers are well-aligned. Let dry for several hours.

Carefully spread glue on the top white part of the pixels on the ring. Press the 3-layer acrylic ring on top and let dry.

If you want, you can shorten the battery wires. Cut, re-solder, and heat shrink.

## Photos

Don't mind the weird lines! They're an artifact of the Neopixel refresh rate.

![Rainbow Flag Necklace](https://github.com/brightcolorfulflickers/pride_necklace/blob/master/photos/necklace front on.jpg)
![Rainbow Flag Necklace (off)](https://github.com/brightcolorfulflickers/pride_necklace/blob/master/photos/necklace front off.jpg)
![Rainbow Flag Necklace (animation)](https://github.com/brightcolorfulflickers/pride_necklace/blob/master/photos/rainbowchase.jpg)
![Rainbow Flag Necklace (back)](https://github.com/brightcolorfulflickers/pride_necklace/blob/master/photos/necklace back.jpg)

For more process photos, see my [tumblr](http://brightcolorfulflickers.tumblr.com/tagged/pride-necklace).

## VARIANT: Pride Outfit

I also made a slightly more risqué version that I call the [pride outfit](http://brightcolorfulflickers.tumblr.com/tagged/pride-outfit). I used two Neopixel rings and a Gemma. I sewed the rings and Gemma into a cloth bikini with one ring on each side. That version uses the prideoutfit.ino code. Simply solder the two rings to the same pin and they will both receive the same data.
