reset
set xlabel "longitude"
set ylabel "latitude"
set title "wind vector map"
set autoscale noextend
set xtics 
set ytics
set terminal png size 1920,1080
set output "wind.png"

plot "gnuplot_wind.csv" using 5:4:($2*pi)/180:3 with vectors  notitle
