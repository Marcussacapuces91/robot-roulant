// surface(file="raspi.png", invert=true, center=true);



*minkowski() {
    cube([85-6,56-6,1.5],center=true);
    cylinder(r=3,h=0.0001,$fn=50,center=true);
}



ep = 1.5;

difference() {
    minkowski() {
        cube([85-6+2*ep,56-6+2*ep,10],center=true);
        cylinder(r=3,h=0.0001,$fn=50,center=true);
    }
    
    translate([0,0,ep]) minkowski() {
        cube([85-6,56-6,10],center=true);
        cylinder(r=3,h=0.0001,$fn=50,center=true);
    }
 
    translate([5/2,0,3*ep]) cube([85+5,56,10],center=true);

    translate([-(85-65)/2,-5/2,3*ep]) cube([65,56+5,10],center=true);
    
    translate([-85/2,0,+ep]) cube([5,12,10],center=true);
    
    for (x=[3.5,58+3.5],y=[3.5,49+3.5]) translate([x-85/2+10,y-56/2,-0.25-2*ep]) cylinder(d=1.5,h=5,$fn=20,center=true);
}

for (x=[3.5,58+3.5],y=[3.5,49+3.5]) translate([x-85/2,y-56/2,-0.25-2*ep]) difference() {
    cylinder(d1=5,d2=3,h=ep+1,$fn=20,center=true);
    cylinder(d=1.5,h=5,$fn=20,center=true);
}
    
