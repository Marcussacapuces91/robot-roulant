// %cube([600,124.3,5],center=true);


*difference() {
// Base    
    cube([500,300,5],center=true);
// Suppression angles avant
    for(i=[-1,1]) translate([-250,i*150,0]) rotate([0,0,i*45]) cube([150,300/sqrt((3+2*sqrt(2))),7],center=true);
}


/**
 * Moteur avec réducteur de longueur variable.
 * @see https://ae01.alicdn.com/kf/HTB1C.FgNXXXXXaJapXXq6xXFXXXq/222102736/HTB1C.FgNXXXXXaJapXXq6xXFXXXq.jpg?size=104274&height=289&width=800&hash=91e54597dd2dd8c9c6fd6ef7daafff6d
 * @param L Longueur du réducteur
 */
module moteur(L=23.0) {
// Moteur
     color("lightgrey") translate([0,0,L+31/2+0.05]) cylinder(d=24.4,h=31-0.1,center=true);
// Place CI    
     color("green") translate([0,0,L+31+2/2]) cylinder(d=24.4,h=2,center=true);
// Capteur
     color("grey") translate([0,0,L+40-6/2]) cylinder(d=14,h=6,center=true);
    
    color("lightgrey") difference() {
// Réducteur
        translate([0,0,L/2]) cylinder(d=24.4,h=L,center=true);
        for(i=[-1/2,1/2]) {
#            translate([0,i*17,0]) cylinder(d=0.5,h=10,center=true);
            translate([0,i*17,0]) cylinder(d=3,h=10,$fn=20,center=true);
        }
    }
// Épaulement
    color("yellow") translate([0,0,-2.5/2]) cylinder(d=7,h=2.5,$fn=20,center=true);
// Axe de sortie
    color("lightgrey") translate([0,0,-12/2]) cylinder(d=4,h=12,,$fn=20,center=true);
}

// Module 3D avant
module avant() {  
    difference() {
// Forme générale
        translate([-206,0,-17.5-2.5]) cube([87.9,300,35],center=true);
// Perçages supérieurs
        e=11.25;
        for (i=[-5*e,-3*e,-e,e,3*e,5*e]) translate([-100,0,-17.5-2.5]) rotate([0,0,i]) translate([-142.5,0,0]) cylinder(d=3.5,h=45,$fn=20,center=true);
// Creux circulaire
        translate([-100,0,-17.5-2.5]) cylinder(d=270,h=37,center=true);
// Suppression angles avant
        for(i=[-1,1]) translate([-250,i*150,-17.5-2.5]) rotate([0,0,i*45]) cube([150,300/sqrt((3+2*sqrt(2))),37],center=true);
// Formes capteurs HS
        for (i=[-1,0,1]) translate([-250+12+abs(i)*40,i*97.5,-20+2.5]) rotate([0,-90,-i*45]) {
// Bloc
            translate([0,0,-25/2+0.5]) cube([21,46,25],center=true);
// Quartz & connecteur
            for (j=[-8,8]) translate([j,0,-25/2+0.5+12.5]) cube([5,10,10],center=true);
            for (y=[-12.75,12.75]) translate([0,y,0]) cylinder(d=16,h=12.3,$fn=50);
         }
    }
}

/**
 * Construction
 */
difference() {
// Base    
    color("orange") cube([500,300,5],center=true);
// Suppression angles avant
    for(i=[-1,1]) translate([-250,i*150,0]) rotate([0,0,i*45]) cube([150,300/sqrt((3+2*sqrt(2))),7],center=true);
}

// plaque ventrale
color("orange") translate([250/2-(250-87.9),0,-35]) cube([250,300,5],center=true);

// Bares latérales 30x30x250
color("lightgrey") for (i=[-1,1]) translate([-37,i*135,-17.5]) cube([250,30,30],center=true);

z = -18;
// Roue
for (i=[-1,1]) {
    translate([150,i*130,z]) rotate([0,90,-i*90]) moteur();
    translate([150,i*130+i*15,z]) rotate([0,90,90]) cylinder(d=65,h=20,center=true);
}

// Bloc 3D avant avec support capteurs US
avant();

// Roulette
translate([-180,0,-37.5]) rotate([90,0,0]) cylinder(d=25,h=15,center=true);