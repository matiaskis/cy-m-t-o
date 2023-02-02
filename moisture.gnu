reset

set title "interpolated map"
set xlabel "longitude"
set ylabel "latitude"
set zlabel "moisture"
set xyplane relative 0
set autoscale noextend
set terminal png size 1920,1080
set output "moisture.png"
set palette rgbformulae 2,4,12
set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
set border 4095 front lt black linewidth 1.000 dashtype solid
set view map scale 1
set pm3d implicit at b
set dgrid3d 50,50
set pm3d map interpolate 5,5 flush begin nohidden3d
splot "gnuplot_m.csv" using 2:1:3 with pm3d notitle
