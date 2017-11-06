use <_parts.scad>
use <_utils.scad>
include <_params.scad>
use <Chamfers\Chamfer.scad>

lcd_w = 22;
lcd_h = 11;

lcd_w2 = 22 * 1.1;
lcd_h2 = 11 * 1.1;

btn_y = 38;
btnA_x = 24;
btnB_x = 44;

btn_y_offset = 2;
btn_x_offset = 1;

btn_l = 0.5;
btn_r = 2;
btn_bw = 8;
btn_bh = 12;

module btn_cut() {
  
  l = btn_l;
  r = btn_r;
  bw = btn_bw;
  bh = btn_bh;
  
  //rotate([0,0,180])
  translate([-bw/2, -bh+r/2])
  union() {
  
  cube([l,bh,10], false);
  
  translate([bw-l, 0,0])
    cube([l,bh,10], false);
  
  translate([r,bh+r-l,0])
    cube([bw-2*r,l,10], false);
  
  translate([r, bh,0])
    rotate([0, 0, 90])
      intersection() {
        difference() {
          cylinder(20, r, r, true);
          cylinder(20, r-l, r-l, true);
        }
        
        cube([10,10,10], false);
      }
      
  translate([bw-r, bh,0])
    rotate([0, 0, 0])
      intersection() {
        difference() {
          cylinder(20, r, r, true);
          cylinder(20, r-l, r-l, true);
        }
        
        cube([10,10,10], false);
      }
      
    translate([0, 0, -1])
    cube([bw,2,2], false);
    
  }
  
}

module btn_press() {
  
  l = btn_l;
  r = btn_r;
  bw = btn_bw;
  bh = btn_bh;
  
  translate([-bw/2 + l, -r/2 -l  , 0])
  difference () {
    cube([bw - 2*l,2 * r, 1], false);
    
    rounderer(0, 2*r, 90, r - l);
    rounderer(bw-2*l, 2*r, 0, r-l);
    rounderer(bw-2*l, 0, -90, r-l);
    rounderer(0, 0, 180, r-l);
  }
  
  
}


module top_panel() {

  lcd_x = w/2;
  lcd_y = 51.5 + (lcd_h2 / 2);

  union() {
    
    difference () {

      panel();

      // LCD
      translate([lcd_x, lcd_y,0])
        cube([lcd_w2,lcd_h2,10], true);
      
      // chamfer
      translate([lcd_x - lcd_w2/2 - 3, lcd_y - lcd_h2/2 -3, 1])
        chamferCube(lcd_w2 + 6, lcd_h2 + 6, 10, 3);
      
      translate([btnA_x + btn_x_offset, btn_y + btn_y_offset, 0])
        btn_cut();
      
      translate([btnB_x - btn_x_offset, btn_y + btn_y_offset, 0])
        btn_cut();
    }
    
    translate([btnA_x + btn_x_offset, btn_y + btn_y_offset, 1.5])
      btn_press();
    
    translate([btnB_x - btn_x_offset, btn_y + btn_y_offset, 1.5])
      btn_press();
  }
  
}



top_panel();

//btn_cut();
//btn_press();

// buttons
/*
translate([btnA_x, btn_y,-3]) cylinder(5, 1.5, 1.5, true);
translate([btnB_x, btn_y,-3]) cylinder(5, 1.5, 1.5, true);
*/


