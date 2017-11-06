include <_params.scad>

use <top-housing.scad>
use <btm-housing.scad>
use <top-panel.scad>
use <btm-panel.scad>

translate([w, 0, 12 + 1.5 + 5.5])
  rotate([0,180,0])
    top_housing();

translate([0,0,2])
  btm_housing();


translate([0,0,12 + 1.5 + 5.5])
  top_panel();

translate([w,0,2])
  rotate([0,180,0])
    btm_panel();
