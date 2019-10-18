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

module barreAvant(ep = 50) {
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
}

module barreArriere(ep = 50) {
difference() {
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
        for (y=[-140,140]) translate([-130,y,0]) cube([185,20,ep],center=true);
    }
            for (x=[-45,-135,-155,-220],y=[-140,140]) translate([x,y,0]) cylinder(d=3,h=70,$fn=10,center=true);
            for (y=[-55,55]) translate([-255,y,0]) cylinder(d=3,h=70,$fn=10,center=true);
            for (y=[-35,35]) translate([-257.5,y,0]) cylinder(d=3,h=70,$fn=10,center=true);
    }
}

module US(ep=50) {
translate([0,0,-ep/2]) cube([21.5,45.5,ep],center=true);
for (i=[-1,1]) translate([0,i*12.77,5.75]) cylinder(d=16.5,h=12.5,$fn=50,center=true);
for (x=[-8,8]) hull() for(y=[-3,3]) translate([x,y,3.5/2]) cylinder(d=5,h=4,$fn=20,center=true);
}

/**
 * Cloche des roues arrières
 * diam 40 pour permettre la bonne rotation de la roue
 * profondeur réglable avec le paramètre h
 */
module cloche(h=35) {
    difference() {
        hull() for (x=[-30,30],y=[-30,30]) translate([x,y,0]) cylinder(d=22,h=(h+2),$fn=40,center=true);
//        cube([82,82,h+2],center=true);
        translate([0,0,-4]) cylinder(r=40,h=h+2,$fn=50,center=true);
        translate([0,0,h/2-3.5]) cube([50,40,5],center=true);
        for (x=[-36.5/2,36.5/2],y=[-27.5/2,27.5/2]) {
            translate([x,y,h/2]) cylinder(d=5,h=5,$fn=20,center=true);
        }
        for (e=70,x=[-e/2,e/2],y=[-e/2,e/2]) {
            translate([x,y,-h/2]) cylinder(d=3,h=20,$fn=20,center=true);
        }
    }
}

*translate([0,0,-4.5]) color("brown") plaqueDessous();

// Roues avant
*for (y=[-140,140]) translate([0,y,20]) rotate([90,0,0]) cylinder(d=67,h=25,center=true);


// m = [1,5], 0 tous
m=0;
intersection() {
// Epaisseur latérale 50mm
    translate([0,0,25]) color("white") union() {
        barreArriere(50);
// Cloches roues arrières
        for (i=[-1,1]) translate([-189.5,i*90,18.5-25]) cloche();
    }
    if (m==1) {
        translate([-70,-140,30]) cube([150,50,70], center=true);
    } else if (m==2) {
        translate([-70,140,30]) cube([150,50,70], center=true);
    } else if (m==3) {
        translate([-220,-100,30]) cube([150,110,70], center=true);
    } else if (m==4) {
        translate([-220,100,30]) cube([150,110,70], center=true);
    } else if (m==5) {
        translate([-220,0,30]) cube([150,90,70], center=true);
    }
    
    
}

// Plaque dessus
*translate([0,0, 59-4.5]) rotate([180,0,0]) plaqueDessous();


