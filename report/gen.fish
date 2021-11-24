#!/usr/bin/fish

if not test -d tex-output
	mkdir tex-output
end

latexmk	-output-directory=tex-output -shell-escape -pdf -pdflatex=xelatex report.tex
