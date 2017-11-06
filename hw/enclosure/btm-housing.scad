use <_utils.scad>
use <_parts.scad>

include <_params.scad>

module btm_housing() {
  
  difference() {
    housing(10);
    
    // antenna
    translate([w - antenna_x, h, -antenna_h/2 + antenna_h + 10 - 4])
      cube([antenna_w, 10, antenna_h], true);
    
    // switch
    translate([19.5, h, 10 - 5.5 + 5.5/2])
      cube([7, 10, 5.5], true);
    
    // connector
    translate([w - 19.2, 0, 10 - 3 + 3/2])
      cube([13, 10, 3], true);
    
    
    // wemos cutout
    translate([7 + 27/2, 10/2 + 1.5, 10 - 6 + 6/2])
      cube([27, 10, 6], true);
    
    // USB connector
    translate([18, 0, 5/2 + 10 - 5 - 2])
      cube([9, 10, 5], true);    
  }
}

btm_housing();


   