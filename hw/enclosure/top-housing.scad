use <_utils.scad>
use <_parts.scad>

include <_params.scad>

bhl = 5.5;

module top_housing() {
  
  difference() {
    housing(bhl);
    
    translate([antenna_x, h, -antenna_h/2 + bhl + antenna_h - 1.5])
      cube([antenna_w, 10, antenna_h], true);
  }
}

top_housing();




