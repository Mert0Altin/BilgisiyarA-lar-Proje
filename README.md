# BilgisiyarAglariProje
ilk olarak ns-3'ü şu şekilde kurduk

git clone https://gitlab.com/nsnam/ns-3-dev.git,

cd ns-3-dev


ardından gerekli bağlantıları kurduk

./waf configure --enable-examples --enable-tests

./waf build

 5G LENA modülünü indirdik

 git clone https://gitlab.com/cttc-lena/nr.git
 
cd nr

ns-3'ün bulunduğu dizini belirledik

export NR_MODULE_PATH=`pwd`

export NS3_DIR=../ns-3-dev

5G modülünü ns-3 ile entegre ettik

cd $NS3_DIR

./waf configure --enable-modules=all --with-nr=$NR_MODULE_PATH

./waf build

SUMO'yu kurduk

sudo apt-get install sumo sumo-tools sumo-doc
