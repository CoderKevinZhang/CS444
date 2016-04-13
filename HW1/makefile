TEX 	= tex -shell-escape
BIBTEX	= bibtex
DVIPS	= dvips
DVIPDF  = dvipdft
XDVI	= xdvi -gamma 4
GH		= gv

TARGET =  hw1 



all: 
	latex hw1.tex
	dvips -R -Poutline -t letter hw1.dvi -o hw1.ps
	ps2pdf hw1.ps
	rm hw1.aux
	rm hw1.dvi
	rm hw1.ps
	rm hw1.out

clean:
	rm -f *.pdf *.ps *.dvi *.out *.log *.aux *.bbl *.blg *.pyg

.PHONY: all show clean ps pdf showps
