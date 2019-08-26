*color("grey") cube([33,26.2,3],center=true);

*for (x=[-33/2+8.6+1.75, -33/2+25+1.75],y=[-12.5/2-1.75,12.5/2+1.75]) translate([x,y,0]) cylinder(r=0.1, h=10, center=true);


difference() {
    union() {
        translate([10/2,0,4/2]) cube([33+10,26.2+40,1],center=true);

        translate([-28+1.5,0,-11.63]) rotate([0,90,0]) difference() {
            cylinder(r=36, h=22, $fn=100, center=true);
            translate([0,0,-1]) cylinder(r=35, h=22, $fn=100, center=true);
            translate([11.870,0,0]) cube([50,100,30],center=true);
            for (x=[-34.1,34.1]) translate([-14,x,0]) cube([2,2,30],center=true);
        }
    }
    
    rotate([0,0,-45]) translate([-36-8,0,12.5]) cube([30,70,30],center=true);
    
    for (x=[-33/2+8.6+1.75, -33/2+25+1.75],y=[-12.5/2-1.75,12.5/2+1.75]) translate([x,y,0]) cylinder(d=3,h=6,$fn=20,center=true);
    
}

    