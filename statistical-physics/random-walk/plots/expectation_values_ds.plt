set terminal pngcairo size 1200,600 enhanced font 'Verdana,12'
set output "plots/expectation_values_ds.png"
set xrange [0:1000]
set yrange [-5:*]

set multiplot layout 1,2

set title "simulation"
plot "data/expectation_values_ds.dat" using 1:2 with lines title "{/Symbol m}", "data/expectation_values_ds.dat" using 1:3 with lines title "{/Symbol s}"

set title "D = 4.34517"
plot sqrt(2*4.34517*x) with lines linetype 2 title "sqrt(2Dt)"

unset multiplot
set output