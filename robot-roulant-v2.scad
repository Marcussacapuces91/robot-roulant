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

module barres(ep = 50) {
// Barre front
    difference() {
        translate([120,0,0]) cube([20,124,ep],center=true);    
// Bizots côté 
        for (i=[-1,1]) rotate([0,0,i*45/2]) translate([130,i*17.51,0]) cube([30,20,ep+2],center=true);
// Emplacement US
        translate([118.1,0,-14.5+2]) rotate([0,90,0]) US();
// Avants trous        
        for(y=[-50,50]) translate([120,y,-15]) cylinder(d=3,h=21,$fn=10,center=true);
    }

    *for(y=[-50,50]) translate([120,y,-30]) cylinder(d=0.5,h=20,center=true);

// Barres gauche et droite
    for (i=[-1,1]) difference() {
        translate([103.85/sqrt(2),i*147.68/sqrt(2),0]) rotate([0,0,i*45]) cube([20,140,ep],center=true);
        translate([0,i*145,0]) cube([70,40,ep+2],center=true);
        translate([0,i*160,0]) cube([100,20,ep+2],center=true);
// Bizots côté 
        rotate([0,0,i*45/2]) translate([130,i*(17.51-20),0]) cube([30,20,ep+2],center=true);
// Emplacement US
        translate([85.1,i*90,-14.5+2]) rotate([0,90,i*45]) US(20);
// Avants trous        
        for(y=[-45,45]) rotate([0,0,45]) translate([125,15+y,-15]) cylinder(d=3,h=21,$fn=10,center=true);
    }
    
// Barres côtés et arrière
*    difference() {
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

module US(ep=50) {
translate([0,0,-ep/2]) cube([21,45.5,ep],center=true);
for (i=[-1,1]) translate([0,i*12.77,5.75]) cylinder(d=16,h=12.5,$fn=50,center=true);
for (x=[-8,8]) hull() for(y=[-3,3]) translate([x,y,3.5/2]) cylinder(d=5,h=4,$fn=20,center=true);
}

*translate([0,0,-4.5]) color("brown") plaqueDessous();

// Roues avant
*for (y=[-140,140]) translate([0,y,20]) rotate([90,0,0]) cylinder(d=67,h=25,center=true);

// Epaisseur latérale 50mm
translate([0,0,25]) color("white") barres(50);

// Plaque dessus
* translate([0,0, 59-4.5]) rotate([180,0,0]) plaqueDessous();


