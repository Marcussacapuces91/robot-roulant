
module plaqueDessous() {
    difference() {
        intersection() {
            translate([-200+130,0,0]) cube([400,300,9], center=true);

            cylinder(r=270,h=9,center=true,$fn=100);

            translate([-228.5/sqrt(2),0,0]) rotate([0,0,45]) cube([500,500,10],center=true);
        }

        for(y=[-165+25,165-25]) {
            translate([0,y,0]) cube([50,30,10],center=true);
            translate([0,y,10]) rotate([0,45,0]) cube([50,30,50],center=true);
        }
    }
}

module barres(ep = 40) {
// Barre front
    translate([120,0,0]) cube([20,124,ep],center=true);

// Barres gauche et droite
    for (i=[-1,1]) difference() {
        translate([103.85/sqrt(2),i*147.68/sqrt(2),0]) rotate([0,0,i*45]) cube([20,140,ep],center=true);
        translate([0,i*145,0]) cube([70,40,ep+2],center=true);
        translate([0,i*160,0]) cube([100,20,ep+2],center=true);
    }
    
// Barres côtés et arrière
    difference() {
        intersection() {
            cylinder(r=270,h=ep,$fn=200,center=true);
            translate([-300/2-35,0,0]) cube([300,300,ep+2],center=true);
        }
        intersection() {
            cylinder(r=250,h=ep+2,$fn=200,center=true);
            translate([-250/2-30,0,0]) cube([250,260,ep+2],center=true);
        }
    }
}

translate([0,0,-4.5]) color("brown") plaqueDessous();

// Roues avant
for (y=[-140,140]) translate([0,y,20]) rotate([90,0,0]) cylinder(d=67,h=25,center=true);

translate([0,0,20]) color("white") barres(40);
translate([0,0, 49-4.5]) rotate([180,0,0]) plaqueDessous();