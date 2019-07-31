

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
        cube([90+20,300,30],center=true);
// Perçages supérieurs
        for (e=11.25, i=[/*-5*e,*/-3*e,-1*e,1*e,3*e/*,5*e*/]) translate([-100+206,0,0]) rotate([0,0,i*1.5]) translate([-142.5,0,0]) cylinder(d=3.5,h=45,$fn=20,center=true);
// Creux circulaire
        translate([106,0,0]) cylinder(d=261,h=37,$fn=100,center=true);
// Suppression angles avant
        for(i=[-1,1]) translate([-49.5,i*155.5,0]) rotate([0,0,i*45]) cube([150,300/sqrt((3+2*sqrt(2))),31],center=true);
// Formes capteurs US
        for (i=[-1,0,1]) translate([206-250+1+abs(i)*(20+0.5),i*(77.5+0),0]) rotate([0,-90,-i*45]) {
// Bloc
            translate([0,0,-25/2+0.5]) cube([22,48,40],center=true);
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
// Base : medium 30x30x5 mm
    color("orange") cube([300,300,9],center=true);
// Suppression angles avant
    for(i=[-1,1]) translate([-150,i*150,0]) rotate([0,0,i*45]) cube([150,300/sqrt((3+2*sqrt(2))),10],center=true);
}

// plaque ventrale
*color("orange") translate([250/2-(250-87.9),0,-35]) cube([250,300,5],center=true);

// Roues motorisées
for (x=-70, z=-18, i=[-1,1]) {
    translate([x,i*130,z]) rotate([0,90,-i*90]) moteur();
    translate([x,i*130+i*15,z]) rotate([0,90,90]) cylinder(d=65,h=20,center=true);
}

// Roulettes arrières
for (x=130, y=[-120,120]) {
    translate([x,y,-37.5]) rotate([90,0,0]) cylinder(d=25,h=15,center=true);
}    
   
// Bares latérales 30x30x250 (2x190, 1x240)
color("lightgrey") {
    for (i=[-1,1]) translate([55,i*135,19.5]) cube([190,30,30],center=true);
    translate([135,0*135,19.5]) cube([30,240,30],center=true);
}

// Bloc 3D avant avec support capteurs US
translate([-95,0,19.5]) avant();

color("lightgrey") {
    for (x=[-47,135], y=[-135,135]) translate([x,y,129.5]) cube([30,30,190],center=true);
//    translate([135,0*135,19.5]) cube([30,240,30],center=true);
}

