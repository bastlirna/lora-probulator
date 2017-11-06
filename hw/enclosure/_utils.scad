

module rounderer(x, y, rot, r = 3) {
  //r = 3;
  l = 20;
  
  translate([x, y, 0]) {
    rotate([0, 0, rot]){
      translate([-r, -r, -l]) {
        difference() {
          cube([2*r, 2*r, 2*l]);
          cylinder(2*l, r, r, false);
        }
      }
    }
  }
}



module trimmer(a, rot) {
  
  l = 200;
  
  rotate([a,0, rot])
    translate([-l/2, -l/2, 0])
      cube([l, l, 10]);
  
  
}



trimmer(10, 90);