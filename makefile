JAVAC=javac
JAVA=java
JAR=core.jar
SRC=init.java
CLASS=init

all:compile run

compile:
	$(JAVAC) -cp $(JAR) $(SRC)

run:
	$(JAVA) -cp ".;$(JAR)" $(CLASS)

clean:
	del *.class 
