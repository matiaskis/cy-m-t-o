reset

set title "interpolated map"
set xlabel "longitude"
set ylabel "latitude"
set zlabel "heigth"
set xyplane relative 0
set autoscale noextend
set terminal png size 1920,1080
set output "height.png"
set palette rgbformulae 4,6,11
set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
set border 4095 front lt black linewidth 1.000 dashtype solid
set view map scale 1
set pm3d implicit at b
set dgrid3d 50,50
set pm3d map interpolate 5,5 flush begin nohidden3d
splot "gnuplot_height.csv" using 4:3:2 with pm3d notitle
