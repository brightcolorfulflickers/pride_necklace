// This design is a cover for Adafruit's 16-Neopixel ring combined with the Gemma microcontroller into a necklace.
// Author: brightcolorfulflickers - instagram, tumblr, github
// September 2016

ring_h = 5; // height of the inner ring perpendicular to the PCB
outer_r = 44.5/2; // from OD posted on Adafruit product page
inner_r = 31.2/2; // from ID posted on Adafruit product page
case_ring_thick = 1; // thickness of the inner ring perpendicular to the PCB
case_top_thick = 1; // the thickness of the diffusion layer on top of the LEDs
wire_slot = 2; // width of slot for wires
top_cutout_angle = 60; // half sweep of top cutout (total is this x 2) since the Gemma presses up against the Neopixel ring
bottom_cutout_angle = 20; // half sweep of bottom cutout (total is this x 2) to allow space for battery & wire
fnval = 100; // resolution of render

module ring_case() {
    difference() {
        union() {
            translate([0,0,case_top_thick]) difference() {
            cylinder(ring_h,inner_r,inner_r, false, $fn=fnval);
            cylinder(ring_h,inner_r-case_ring_thick,inner_r-case_ring_thick, false, $fn=fnval);
            }

            difference() {
                cylinder(case_top_thick,outer_r,outer_r, false, $fn=fnval);
                cylinder(case_top_thick,inner_r-case_ring_thick,inner_r-case_ring_thick, false, $fn=fnval);
            }
        }
        //Cut out slots for the wires.
        translate([-wire_slot/2,0,case_top_thick]) cube([wire_slot,inner_r,ring_h], false);
        translate([-wire_slot/2,-inner_r,case_top_thick]) cube([wire_slot,inner_r,ring_h], false);
        
        translate([-inner_r,-wire_slot/2,case_top_thick]) cube([inner_r,wire_slot,ring_h], false);
    }
}

/* 
 * Excerpt from... 
 * 
 * Parametric Encoder Wheel 
 *
 * by Alex Franke (codecreations), March 2012
 * http://www.theFrankes.com
 * 
 * Licenced under Creative Commons Attribution - Non-Commercial - Share Alike 3.0 
*/
 
module arc( height, depth, radius, degrees ) {
    // This dies a horible death if it's not rendered here 
    // -- sucks up all memory and spins out of control 
    render() {
        difference() {
            // Outer ring
            rotate_extrude($fn = 100)
                translate([radius - height, 0, 0])
                    square([height,depth]);
         
            // Cut half off
            translate([0,-(radius+1),-.5]) 
                cube ([radius+1,(radius+1)*2,depth+1]);
         
            // Cover the other half as necessary
            rotate([0,0,180-degrees])
            translate([0,-(radius+1),-.5]) 
                cube ([radius+1,(radius+1)*2,depth+1]);
         
        }
    }
}

difference() {
    ring_case();
    //This part cuts out the top arc since the Gemma presses against the Neopixel ring. Widened from v1.
    translate([0,0,case_top_thick]) arc(case_ring_thick,ring_h,inner_r,top_cutout_angle);
    translate([0,0,case_top_thick]) mirror([1,0,0]) arc(case_ring_thick,ring_h,inner_r,top_cutout_angle);
    
    //This part cuts out the bottom arc to allow room for the battery wires.
    translate([0,0,case_top_thick]) mirror([0,1,0]) arc(case_ring_thick,ring_h,inner_r,bottom_cutout_angle);
    translate([0,0,case_top_thick]) mirror([1,0,0]) arc(case_ring_thick,ring_h,inner_r,-bottom_cutout_angle);
    
    
}