#include files.chh
#include strings.chh
\
%<TABLE_SIZE=2>\
%<REF_FILE=references.txt>\
%<EXTREF_FILE=refextern.txt>\
%<refhash=%hash()>\
%<xrefhash=%hash()>\
\
%define(link,page,text,
     <A HREF="%<page>.html">%text</A>
)\
\
%define(flink,url,
     <A HREF="http://%<url>">%url</A>
)\
\
%define(tbl2line,first,second,
     <TR>
          <TD>%first</TD>
          <TD>%second</TD>
     </TR>
)\
\
%define(tbl2bline,first,second,
     %tbl2line(<B>%first</B>,%second)
)\
\
%define(list,heading,
     %if(%[!%equal(%heading,%'')],<B>%<heading>:</B>)
<UL>
)\
\
%define(endlist,
     </UL>
)\
\
%define(item,line,
     <LI>%<line></LI>
)\
\
%define(litem,part1,part2,
     <LI>%<part1> %'(' %flink(%<part2>) %')'</LI>
)\
\
%define(nitem,part1,part2,
     <LI><B>%<part1></B> -- %<part2></LI>
)\
\
%define(llitem,tlink,text,
     <LI>%link(%tlink,%tlink) -- %text</LI>
)\
\
%define(nlitem,part1,part2,link1,
     <LI>%<part1> -- %<part2> %'('<B>note</B>: see %link(%<link1>,%<link1>)%')'</LI>
)\
\
%define(nlritem,part1,part2,ref,
     %<checkhash=%refhash{%ref}>
     <LI>%<part1> -- %<part2> %'('<B>note</B>: see %link(%ref,%ref)%')'</LI>
)\
\
%define(refpop,
     %<file=%fopen(%REF_FILE)>\
     %until(%feof(%file),\
          %<line=%fgets(%file)>\
          %if(%[%smatch(%' :: ', %line)!=-1],\
               %<linelist=%ssplit(%' :: ', %line)>\
               %<refhash{%sremovews(%linelist[0])}=%sremovews(%linelist[1])>\
          )\
     )\
     %fclose(%file)\
)\
\
%define(extrefpop,
     %<file=%fopen(%EXTREF_FILE)>\
     %until(%feof(%file),\
          %<line=%fgets(%file)>\
          %if(%[%smatch(%' :: ', %line)!=-1],\
               %<linelist=%ssplit(%' :: ', %line)>\
               %<refname=%sremovews(%linelist[0])>\
               %ldelete(%&linelist, 0)\
               %<xrefhash{%refname}=%linelist>\
          )\
     )\
     %fclose(%file)\
)\
\
%define(lxritem,ref,
     %<reflist=%xrefhash{%ref}>\
     <LI>%sremovews(%reflist[0]) \
     %for(i,1,%[%llength(%reflist)-1], \
          %' <NOBR>( '%flink(%sremovews(%reflist[%i]))%' )</NOBR>'\
     )\
     </LI>
)\
\
%define(lritem,ref,
     %llitem(%ref,%refhash{%ref})\
)\
\
%define(tablec,heading,
     <TABLE BORDER=0 CELLPADDING=1 CELLSPACING=3 BGCOLOR="#9999FF">
          <TR>
     <TH COLSPAN=%TABLE_SIZE ALIGN="left">%heading</TH>
     </TR>
)\
\
%define(tablel,heading,
     <TABLE BORDER=1 CELLPADDING=1 CELLSPACING=1>
     <TR>
          <TH COLSPAN=%TABLE_SIZE ALIGN="center">%heading</TH>
     </TR>
)\
\
%define(table,heading,args::1,
     %<num=2>
     %if(%args, %<num=%args[0]>)
     %<TABLE_SIZE=%num>
     %tablec(%heading)
)\
\
%define(tblhead,heading,
     <TR>
          <TH COLSPAN=%TABLE_SIZE ALIGN="left"><BR></TH>
     </TR>
     <TR>
          <TH COLSPAN=%TABLE_SIZE ALIGN="left">%heading</TH>
     </TR>
)\
\
%define(endtable,
     </TABLE>
)\
\
%define(tbl2link,first,second,
     %tbl2line(first,%flink(%<second>))
)\
\
%define(tblstat,ref,status,
	<TR>
		<TD>%status</TD>
		<TD>%link(%ref,%ref)</TD>
		<TD>%refhash{%ref}</TD>
	</TR>
)\
\
\
\
#! simple expansion macros
\
%define(t_ibecomeroot,
     %item(become root:)
<PRE>
%'% su'
</PRE>\
)\
\
%define(t_user,
     &lt;user&gt;\
)\
\
%define(t_iexitroot,
     %item(exit from root:)
<PRE>
%'# exit'
</PRE>\
)\
