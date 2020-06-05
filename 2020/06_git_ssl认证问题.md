```
$ git clone https://github.com/shaojwa/lceph.git
Cloning into 'lceph'...
fatal: unable to access 'https://github.com/shaojwa/lceph.git/': SSL certificate problem: unable to get local issuer certificate
```
需要
```
git config --global http.sslverify false
```
