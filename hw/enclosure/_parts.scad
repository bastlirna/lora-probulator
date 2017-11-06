use <_utils.scad>
include <_params.scad>

module panel() {
  
    
   difference() {
       
    union() {
      // plášť
     difference() {
        cube([w, h, 2]);
        
        union() {
          rounderer(0,0,180);  
          rounderer(w,0,-90);  
          rounderer(w,h,0);  
          rounderer(0,h,90);  
        }
        
        // ukos
        translate([0,0,1]){
          union() {
            trimmer(12, 0);
            translate([w,0,0]) trimmer(12, 90);
            translate([w,h,0]) trimmer(12, 180);
            translate([0,h,0]) trimmer(12, -90);
          }
        }
        
        // zapuštění pro šrouby
        translate([0,0,1]){
          translate([3.5,3.5,0]) cylinder(10, 3.5, 3.5, false);
          translate([w-3.5,3.5,0]) cylinder(10, 3.5, 3.5, false);
          translate([w-3.5,h-3.5,0]) cylinder(10, 3.5, 3.5, false);
          translate([3.5,h-3.5,0]) cylinder(10, 3.5, 3.5, false);
        }
      }
    }
    
    // vrtani
    translate([3.5,3.5,0]) cylinder(10, 3.2/2, 3.2/2, false);
    translate([w-3.5,3.5,0]) cylinder(10, 3.2/2, 3.2/2, false);
    translate([3.5,h-3.5,0]) cylinder(10, 3.2/2, 3.2/2, false);
    translate([w-3.5,h-3.5,0]) cylinder(10, 3.2/2, 3.2/2, false);
    
  }
  
}



module housing(d) {
  
   difference() {
       
    union() {
      // plášť
     difference() {
        cube([w, h, d]);
        
        union() {
          rounderer(0,0,180);  
          rounderer(w,0,-90);  
          rounderer(w,h,0);  
          rounderer(0,h,90);  
        }
        
        translate([t,t,0])
          cube([w-2*t, h-2*t, d]);
      }

      // domečky pro šrouby
      translate([3.5,3.5,0]) cylinder(d, 3.5, 3.5, false);
      translate([w-3.5,3.5,0]) cylinder(d, 3.5, 3.5, false);
      translate([w-3.5,h-3.5,0]) cylinder(d, 3.5, 3.5, false);
      translate([3.5,h-3.5,0]) cylinder(d, 3.5, 3.5, false);
    }
    
    // vrtani
    translate([3.5,3.5,0]) cylinder(d, 3.2/2, 3.2/2, false);
    translate([w-3.5,3.5,0]) cylinder(d, 3.2/2, 3.2/2, false);
    translate([3.5,h-3.5,0]) cylinder(d, 3.2/2, 3.2/2, false);
    translate([w-3.5,h-3.5,0]) cylinder(d, 3.2/2, 3.2/2, false);
    
  }

}


