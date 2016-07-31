# database table DRIVE user interface

## navigation

id	|	parentid	|	key			  |	display		  |	icon	|	tag
----|-----------|-----------|-------------|-------|---------
1	  |	0			    |	root		  |	root		    |			  |	system
2	  |	1			    |	home		  |	home		    |			  |	main
3	  |	2			    |	about		  |	about us	  |			  |	main
4	  |	2			    |	contact	  |	contact us	|			  |	main
5	  |	2			    |	news		  |	what's new	|			  |	main
9	  |	1			    |	product		|	product		  |			  |	main
10	|	9			    |	qrcommon	|	qrcommon	  |			  |	first
11	|	9			    |	qrframe		|	qrframe		  |			  |	first
12	|	9			    |	qrorm		  |	qrorm		    |			  |	first
13	|	9			    |	qrtest		|	qrtest		  |			  |	first
14	|	9			    |	qrlogger	|	qrlogger	  |			  |	first
15	|	9			    |	qrupdate	|	qrupdate	  |			  |	first
17	|	9			    |	qrcache		|	qrcache		  |			  |	first

![navigation ui](http://img.hoop8.com/1607C/RNe485GN.png)

```cpp
...
class QrNavigation {
...
static bool qrconnect(const QString& path,
                          const QObject *receiver,
                          const char *member);
...
};

//  connect signal and slot by navigaiton path(like java package path)
class SomeService{
public:
  void init() {
    QrNavigation::qrconnect("home.product.qrframe", this, SLOT(onQrFrame()));
  }
private slots:
    void onQrFrame() {}
}
```
[demo : connect signal and slot of navigaiton](https://github.com/Qters/QrFrame/blob/master/chaos/services/product/qrproductservice.cpp#L38)

## system tray

id	| separator	| isvisible	| text	      | icon	| sort	| key
----|-----------|-----------|-------------|-------|-------|-----
1	  | True	    | True	    | setting		  |       | 1	    | setting
2	  | False	    | True	    | about		    |       | 3	    | about
3	  | False	    | True	    | help		    |       | 2	    | help
4	  | True	    | True	    | check update|		    | 4	    | check.update
5	  | False	    | True	    | exit		    |       | 5	    | exit

![sytem tray ui](http://img.hoop8.com/1607C/VpMbSv7G.png)
```cpp
...
class QrSystemTray {
...
static bool qrconnect(const QString& path,
                          const QObject *receiver,
                          const char *member);
...
};

//  connect signal and slot by system tray path(like java package path)
class SomeService{
public:
  void init() {
    QrSystemTray::qrconnect("exit", qApp, SLOT(quit()));
  }
}
```
[demo : connect signal and slot of system tray](https://github.com/Qters/QrFrame/blob/master/chaos/services/main/qrmainservice.cpp#L53)

# workspace 

```cpp
...
class QrWorkspace {
...
static int appendTab(QWidget *widget, QString label);
...
};


QrWorkspace::appendTab(new QPushButton(), "Tab Title");

```
[demo : append tab page to workspace](https://github.com/Qters/QrFrame/blob/master/chaos/services/product/qrproductservice.cpp#L57)
