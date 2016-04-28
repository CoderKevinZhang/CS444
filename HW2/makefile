TEX 	= tex -shell-escape
BIBTEX	= bibtex
DVIPS	= dvips
DVIPDF  = dvipdft
XDVI	= xdvi -gamma 4
GH		= gv

TARGET =  hw2 



all: 
	latex hw2.tex
	dvips -R -Poutline -t letter hw2.dvi -o hw2.ps
	ps2pdf hw2.ps

clean:
	rm -f *.pdf *.ps *.dvi *.out *.log *.aux *.bbl *.blg *.pyg

.PHONY: all show clean ps pdf showps
