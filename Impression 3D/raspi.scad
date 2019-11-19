// surface(file="raspi.png", invert=true, center=true);

carte = [85,56,1.4];
dessous = 3.80-1.4 + 0.5;

ep = 1.5;


*minkowski() {
    cube([carte.x-6,carte.y-6,carte.z],center=true);
    cylinder(r=3,h=0.0001,$fn=50,center=true);
}

difference() {
    union() {
        difference() {
        // Forme générale    
            minkowski() {
                cube([carte.x - 6 + 2 * ep, carte.y - 6 + 2 * ep, 10],center=true);
                cylinder(r=3, h=0.0001, $fn=50, center=true);
            }

        // Evidemment carte
            translate([0,0,ep]) minkowski() {
                cube([carte.x - 6, carte.y - 6, 10],center=true);
                cylinder(r=3, h=0.0001, $fn=50, center=true);
            }
         
        // Evidemment gros connecteurs
            translate([carte.x/2, 0, ep+dessous+carte.z]) cube([10, carte.y, 10], center=true);

        // Evidemment petits connecteurs
            translate([-(carte.x-65)/2, -5/2, ep+dessous+carte.z]) cube([65,carte.y+5, 10],center=true);

        // Evidemment carte SD    
            translate([-carte.x/2,0,dessous/2-10/2+ep]) cube([5,12,dessous],center=true);
            
        // Trous vis fixation (diam 2)
            for (x=[3.5,58+3.5],y=[3.5,49+3.5]) translate([x-carte.x/2+10,y-carte.y/2,-10/2]) cylinder(d=2,h=5,$fn=20,center=true);
        }    

        // Pieds carte avec trous de fixation
        for (x=[3.5,58+3.5],y=[3.5,49+3.5]) translate([x-carte.x/2,y-carte.y/2,-10/2+dessous/2+ep]) cylinder(d1=8,d2=5,h=dessous+0.01,center=true);
    }

// Pieds carte avec trous de fixation
    for (x=[3.5,58+3.5],y=[3.5,49+3.5]) translate([x-carte.x/2,y-carte.y/2,-10/2+dessous/2+ep]) cylinder(d=2,h=10,$fn=20,center=true);
}
