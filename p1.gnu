reset

set terminal png size 1920, 1080
set title "pressure max, average, min"
set xlabel "station"
set ylabel "pressure"
set xrange [*:*]
set output "p1.png"
set autoscale noextend
set xtics rotate by 45 right
set grid nopolar
set grid xtics mxtics ytics mytics noztics nomztics nortics nomrtics \
nox2tics nomx2tics noy2tics nomy2tics nocbtics nomcbtics
set style data lines
plot "gnuplot_pres_ave.csv" using 0:2:xticlabels(1) smooth mcspline lc 6 lw 2  title "average pressure", \
"gnuplot_pres_max.csv" using 0:2:xticlabels(1) smooth mcspline lc 7 lw 2  title "max pressure", \
"gnuplot_pres_min.csv" using 0:2:xticlabels(1) smooth mcspline lc 7 lw 2  title "min pressure"
