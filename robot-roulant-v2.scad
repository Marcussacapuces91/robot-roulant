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
// Rainure haute (leds)
    translate([118,0,12.5]) cube([20,128,20],center=true);
// Avant-trous        
        for(y=[-50,50]) translate([120,y,0]) cylinder(d=3,h=ep+2,$fn=10,center=true);
    }

// Barres gauche et droite
    for (i=[-1,1]) difference() {
        translate([103.85/sqrt(2),i*147.68/sqrt(2),0]) rotate([0,0,i*45]) cube([20,140,ep],center=true);
        translate([0,i*145,0]) cube([70,40,ep+2],center=true);
        translate([0,i*160,0]) cube([100,20,ep+2],center=true);
// Bizots côté 
        rotate([0,0,i*45/2]) translate([130,i*(17.51-20),0]) cube([30,20,ep+2],center=true);
// Emplacement US
        translate([85.1,i*90,-14.5+2]) rotate([0,90,i*45]) US(20);
// Rainure haute (leds)
    translate([81.86-5,i*94+i*5,12.5]) rotate([0,0,i*45]) cube([20,140,20],center=true);
// Avant-trous        
        for(y=[-45,45]) rotate([0,0,i*45]) translate([125,i*(15+y),0]) cylinder(d=3,h=ep+2,$fn=10,center=true);
            
// Passage roue
        translate([35,i*140,-10]) cube([10,40,ep-20],center=true);
    }


// Barre arrière
    union() {
        intersection() {
            difference() {
                cylinder(r=270,h=ep,$fn=200,center=true);
                cylinder(r=250,h=ep+2,$fn=200,center=true);
                translate([0,0,12.5]) cylinder(r=268,h=20,$fn=200,center=true);
                translate([-258,0,-12]) rotate([0,-90,0]) US(ep);
            }
            translate([-235,0,0]) cube([75,300,60], center=true);
        }
        
// Barres côtés
        for (i=[-1,1]) translate([-130,i*140,0]) cube([185,20,ep],center=true);

    }
}

module US(ep=50) {
translate([0,0,-ep/2]) cube([21.5,45.5,ep],center=true);
for (i=[-1,1]) translate([0,i*12.77,5.75]) cylinder(d=16.5,h=12.5,$fn=50,center=true);
for (x=[-8,8]) hull() for(y=[-3,3]) translate([x,y,3.5/2]) cylinder(d=5,h=4,$fn=20,center=true);
}

translate([0,0,-4.5]) color("brown") plaqueDessous();

// Roues avant
for (y=[-140,140]) translate([0,y,20]) rotate([90,0,0]) cylinder(d=67,h=25,center=true);

// Epaisseur latérale 50mm
translate([0,0,25]) color("white") barres(50);

// Plaque dessus
translate([0,0, 59-4.5]) rotate([180,0,0]) plaqueDessous();
