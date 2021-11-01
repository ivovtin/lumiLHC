#/bin/sh

export PATH=$HOME/.local/bin:/cvmfs/cms-bril.cern.ch/brilconda/bin:$PATH

TIMESTAMPB=1633063232
timeB=`date -d @$TIMESTAMPB +'%m/%d/%y %H:%M:%S'`
TIMESTAMPE=1635741632
timeE=`date -d @$TIMESTAMPE +'%m/%d/%y %H:%M:%S'`
echo "$TIMESTAMPB - $TIMESTAMPE"

#timeB = '10/25/21 00:00:00'
#timeE = '11/01/21 00:00:00'
echo "$timeB - $timeE"

outLumFile="lum.csv"
echo "Out file with luminosity is" $outLumFile

brilcalc lumi --begin "$timeB" --end "$timeE" -c site-local-config.xml -u 1e33/cm2s  --tssec --output-style csv -o $outLumFile
sed -i '/#/d' $outLumFile
sed -i 's/:/,/g' $outLumFile

root -l -b -q 'draw_lumi.C('$TIMESTAMPB', '$TIMESTAMPE', "'$outLumFile'")'
