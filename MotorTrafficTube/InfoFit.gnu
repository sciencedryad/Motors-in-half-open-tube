#-----------------------------------------------------------------
# double log plot

set logscale 

fitend1=10
f1(x)=a1*x+b1
fit [0:log(fitend1)] f1(x) "AnaCorrRho_b.dat" using (log($1)):(log($2)) via a1,b1
g1(x) = (x<fitend1+50)?exp(f1(log(x))):log(-3)

set terminal x11
#set terminal postscript 
set output 'AnaCorr.eps'

plot [:100]"AnaCorrRho_b.dat" u 1:2 w linespoint, g1(x)
#-----------------------------------------------------------------
# log plot
set logscale y

fitend2=20
f2(x)=a2*x+b2
fit [0:fitend2] f2(x) "AnaCorrJ_b.dat" using ($1):(log($2)) via a2,b2
g2(x) = (x<fitend2+20)?exp(f2(x)):log(-3)

set terminal x11
#set terminal postscript 
set output 'AnaCorr.eps'

plot [:100]"AnaCorrJ_b.dat" u 1:2 w linespoint, g2(x)
#-----------------------------------------------------------------


#-------------------------------------------------------
#Rho_b

fitend0=12
f0(x)=a0*x+b0
fit [0:log(fitend0)] f0(x) "AnaCorrRho_b.dat" using (log($1)):(log($2)) via a0,b0
gRho_bPot(x) = (x<fitend0+50)?exp(f0(log(x))):log(-3)

fitbegin1=4;
fitend1=20
f1(x)=a1*x+b1
fit [fitbegin1:fitend1] f1(x) "AnaCorrRho_b.dat" using ($1):(log($2)) via a1,b1
gRho_bExp(x) = (x<fitend1+10)?exp(f1(x)):log(-3)

#-------------------------------------------------------
#J_b

fitend2=5
f2(x)=a2*x+b2
fit [0:log(fitend2)] f2(x) "AnaCorrJ_b.dat" using (log($1)):(log($2)) via a2,b2
gJ_bPot(x) = (x<fitend2+2)?exp(f2(log(x))):log(-3)

#-------------------------------------------------------
#Rho_b_tot

fitbegin4=5
fitend4=100
f4(x)=a4*x+b4
fit [fitbegin4:fitend4] f4(x) "AnaCorrRho_b_tot.dat" using ($1):(log($2)) via a4,b4
gRho_b_totExp(x) = (x<fitend4+10)?exp(f4(x)):log(-3)

#-------------------------------------------------------
#J_b_tot

fitbegin3=5
fitend3=100
f3(x)=a3*x+b3
fit [fitbegin3:fitend3] f3(x) "AnaCorrJ_b_tot.dat" using ($1):(log($2)) via a3,b3
gJ_b_totExp(x) = (x<fitend3+10)?exp(f3(x)):log(-3)

#-------------------------------------------------------

set terminal x11
set terminal postscript 
set output 'AnaCorr.eps'

plot [:130]\
"AnaCorrRho_b.dat" u 1:2 w linespoint, gRho_bPot(x),\
"AnaCorrJ_b.dat" u 1:2 w linespoint,gJ_bPot(x),\
"AnaCorrRho_b_tot.dat" u 1:2 w linespoint,gRho_b_totExp(x),\
"AnaCorrJ_b_tot.dat" u 1:2 w linespoint,gJ_b_totExp(x)  

print "AnaCorrRho_b.dat:    pot", a0
print "AnaCorrJ_b.dat:      pot", a2
print "AnaCorrRho_b_tot.dat:exp", a4
print "AnaCorrJ_b_tot.dat:  exp", a3

