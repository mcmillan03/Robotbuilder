DOCXX = doc++

tex:
	$(DOCXX) -v -t -u -o ref_manual.tex ref_manual.dxx
	latex ref_manual
	latex ref_manual

ps:	tex
	dvips -o ref_manual.ps ref_manual.dvi

html:
	$(DOCXX) ref_manual.dxx

clean:
	\rm -rf ref_manual.ps ref_manual.tex ref_manual.aux \
		ref_manual.toc ref_manual.dvi ref_manual.log core *.swp *~\
		*.html *.gif dxx* *.class gifs.db .1.html
