cd C:\Evinrude\Evinrude-master\target
java -jar cami2pnml-2.1.8-withDependencies.jar -c2p %1 -o %2.pnml
<nul (set/p z=) >%2_final.pnml
java Grap %2.pnml %2_final.pnml
exit