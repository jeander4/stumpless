!include <win32.mak>

INCDIR = $(BASEDIR)\include
SRCDIR = $(BASEDIR)\src
TESTDIR = $(BASEDIR)\test
OUTDIR = $(BASEDIR)\build
STUMPLESSFLAGS = -D__STUMPLESS_HAVE_CRT_SECURE_FUNCTIONS -nologo
STUMPLESSOBJECTS = $(OUTDIR)\src\adapter.obj \
                   $(OUTDIR)\src\adapter\base.obj \
                   $(OUTDIR)\src\adapter\initializer.obj \
                   $(OUTDIR)\src\boolean.obj \
                   $(OUTDIR)\src\comparator.obj \
                   $(OUTDIR)\src\comparator\base.obj \
                   $(OUTDIR)\src\comparator\initializer.obj \
                   $(OUTDIR)\src\configuration.obj \
                   $(OUTDIR)\src\container\dictionary.obj \
                   $(OUTDIR)\src\container\dictionary\const_iterator.obj \
                   $(OUTDIR)\src\container\list.obj \
                   $(OUTDIR)\src\container\list\adapter.obj \
                   $(OUTDIR)\src\container\list\comparator.obj \
                   $(OUTDIR)\src\container\list\const_iterator.obj \
                   $(OUTDIR)\src\container\list\const_iterator\adapter.obj \
                   $(OUTDIR)\src\container\list\const_iterator\comparator.obj \
                   $(OUTDIR)\src\container\list\const_iterator\filter.obj \
                   $(OUTDIR)\src\container\list\const_iterator\formatter.obj \
                   $(OUTDIR)\src\container\list\const_iterator\handler.obj \
                   $(OUTDIR)\src\container\list\const_iterator\target.obj \
                   $(OUTDIR)\src\container\list\const_iterator\value.obj \
                   $(OUTDIR)\src\container\list\const_reverse_iterator.obj \
                   $(OUTDIR)\src\container\list\const_reverse_iterator\adapter.obj \
                   $(OUTDIR)\src\container\list\const_reverse_iterator\comparator.obj \
                   $(OUTDIR)\src\container\list\const_reverse_iterator\filter.obj \
                   $(OUTDIR)\src\container\list\const_reverse_iterator\formatter.obj \
                   $(OUTDIR)\src\container\list\const_reverse_iterator\handler.obj \
                   $(OUTDIR)\src\container\list\const_reverse_iterator\target.obj \
                   $(OUTDIR)\src\container\list\const_reverse_iterator\value.obj \
                   $(OUTDIR)\src\container\list\filter.obj \
                   $(OUTDIR)\src\container\list\formatter.obj \
                   $(OUTDIR)\src\container\list\handler.obj \
                   $(OUTDIR)\src\container\list\iterator.obj \
                   $(OUTDIR)\src\container\list\iterator\adapter.obj \
                   $(OUTDIR)\src\container\list\iterator\comparator.obj \
                   $(OUTDIR)\src\container\list\iterator\filter.obj \
                   $(OUTDIR)\src\container\list\iterator\formatter.obj \
                   $(OUTDIR)\src\container\list\iterator\handler.obj \
                   $(OUTDIR)\src\container\list\iterator\target.obj \
                   $(OUTDIR)\src\container\list\iterator\value.obj \
                   $(OUTDIR)\src\container\list\reverse_iterator.obj \
                   $(OUTDIR)\src\container\list\reverse_iterator\adapter.obj \
                   $(OUTDIR)\src\container\list\reverse_iterator\comparator.obj \
                   $(OUTDIR)\src\container\list\reverse_iterator\filter.obj \
                   $(OUTDIR)\src\container\list\reverse_iterator\formatter.obj \
                   $(OUTDIR)\src\container\list\reverse_iterator\handler.obj \
                   $(OUTDIR)\src\container\list\reverse_iterator\target.obj \
                   $(OUTDIR)\src\container\list\reverse_iterator\value.obj \
                   $(OUTDIR)\src\container\list\target.obj \
                   $(OUTDIR)\src\container\list\value.obj \
                   $(OUTDIR)\src\container\queue.obj \
                   $(OUTDIR)\src\container\stack.obj \
                   $(OUTDIR)\src\container\tree.obj \
                   $(OUTDIR)\src\event.obj \
                   $(OUTDIR)\src\event_attribute.obj \
                   $(OUTDIR)\src\exception.obj \
                   $(OUTDIR)\src\exception\handler.obj \
                   $(OUTDIR)\src\filter.obj \
                   $(OUTDIR)\src\filter\base.obj \
                   $(OUTDIR)\src\filter\initializer.obj \
                   $(OUTDIR)\src\formatter.obj \
                   $(OUTDIR)\src\formatter\csv.obj \
                   $(OUTDIR)\src\formatter\initializer.obj \
                   $(OUTDIR)\src\formatter\text.obj \
                   $(OUTDIR)\src\handler.obj \
                   $(OUTDIR)\src\handler\initializer.obj \
                   $(OUTDIR)\src\handler\stream.obj \
                   $(OUTDIR)\src\level.obj \
                   $(OUTDIR)\src\level\initializer.obj \
                   $(OUTDIR)\src\logger.obj \
                   $(OUTDIR)\src\logger\getter.obj \
                   $(OUTDIR)\src\logger\log.obj \
                   $(OUTDIR)\src\logger\sender.obj \
                   $(OUTDIR)\src\output.obj \
                   $(OUTDIR)\src\output\profile.obj \
                   $(OUTDIR)\src\output\profile_initializer.obj \
                   $(OUTDIR)\src\private\event\initializer.obj \
                   $(OUTDIR)\src\private\exception\initializer.obj \
                   $(OUTDIR)\src\private\exception\thrower.obj \
                   $(OUTDIR)\src\private\utility\string.obj \
                   $(OUTDIR)\src\record.obj \
                   $(OUTDIR)\src\record_attribute.obj \
                   $(OUTDIR)\src\target.obj \
                   $(OUTDIR)\src\value.obj \
                   $(OUTDIR)\src\value\constructor.obj \
                   $(OUTDIR)\src\value\profile.obj \
                   $(OUTDIR)\src\value\profile_initializer.obj


all: $(OUTDIR) $(OUTDIR)\stumpless.dll


# build output directories 
$(OUTDIR):
    if not exist "$(OUTDIR)\$(NULL)" mkdir $(OUTDIR)
    if not exist "$(OUTDIR)\src\$(NULL)" mkdir $(OUTDIR)\src
    if not exist "$(OUTDIR)\src\adapter\$(NULL)" mkdir $(OUTDIR)\src\adapter
    if not exist "$(OUTDIR)\src\comparator\$(NULL)" mkdir $(OUTDIR)\src\comparator
    if not exist "$(OUTDIR)\src\container\$(NULL)" mkdir $(OUTDIR)\src\container
    if not exist "$(OUTDIR)\src\container\dictionary\$(NULL)" mkdir $(OUTDIR)\src\container\dictionary
    if not exist "$(OUTDIR)\src\container\list\$(NULL)" mkdir $(OUTDIR)\src\container\list
    if not exist "$(OUTDIR)\src\container\list\const_iterator\$(NULL)" mkdir $(OUTDIR)\src\container\list\const_iterator
    if not exist "$(OUTDIR)\src\container\list\const_reverse_iterator\$(NULL)" mkdir $(OUTDIR)\src\container\list\const_reverse_iterator
    if not exist "$(OUTDIR)\src\container\list\iterator\$(NULL)" mkdir $(OUTDIR)\src\container\list\iterator
    if not exist "$(OUTDIR)\src\container\list\reverse_iterator\$(NULL)" mkdir $(OUTDIR)\src\container\list\reverse_iterator
    if not exist "$(OUTDIR)\src\exception\$(NULL)" mkdir $(OUTDIR)\src\exception
    if not exist "$(OUTDIR)\src\filter\$(NULL)" mkdir $(OUTDIR)\src\filter
    if not exist "$(OUTDIR)\src\formatter\$(NULL)" mkdir $(OUTDIR)\src\formatter
    if not exist "$(OUTDIR)\src\handler\$(NULL)" mkdir $(OUTDIR)\src\handler
    if not exist "$(OUTDIR)\src\level\$(NULL)" mkdir $(OUTDIR)\src\level
    if not exist "$(OUTDIR)\src\logger\$(NULL)" mkdir $(OUTDIR)\src\logger
    if not exist "$(OUTDIR)\src\output\$(NULL)" mkdir $(OUTDIR)\src\output
    if not exist "$(OUTDIR)\src\private\$(NULL)" mkdir $(OUTDIR)\src\private
    if not exist "$(OUTDIR)\src\private\event\$(NULL)" mkdir $(OUTDIR)\src\private\event
    if not exist "$(OUTDIR)\src\private\exception\$(NULL)" mkdir $(OUTDIR)\src\private\exception
    if not exist "$(OUTDIR)\src\private\utility\$(NULL)" mkdir $(OUTDIR)\src\private\utility
    if not exist "$(OUTDIR)\src\value\$(NULL)" mkdir $(OUTDIR)\src\value
    if not exist "$(OUTDIR)\test\function\$(NULL)" mkdir $(OUTDIR)\test\function
    if not exist "$(OUTDIR)\test\function\comparator\$(NULL)" mkdir $(OUTDIR)\test\function\comparator
    if not exist "$(OUTDIR)\test\function\container\$(NULL)" mkdir $(OUTDIR)\test\function\container
    if not exist "$(OUTDIR)\test\function\container\dictionary\$(NULL)" mkdir $(OUTDIR)\test\function\container\dictionary
    if not exist "$(OUTDIR)\test\function\container\list\$(NULL)" mkdir $(OUTDIR)\test\function\container\list
    if not exist "$(OUTDIR)\test\function\container\list\iterator\$(NULL)" mkdir $(OUTDIR)\test\function\container\list\iterator
    if not exist "$(OUTDIR)\test\function\container\list\reverse_iterator\$(NULL)" mkdir $(OUTDIR)\test\function\container\list\reverse_iterator
    if not exist "$(OUTDIR)\test\function\exception\$(NULL)" mkdir $(OUTDIR)\test\function\exception
    if not exist "$(OUTDIR)\test\function\filter\$(NULL)" mkdir $(OUTDIR)\test\function\filter
    if not exist "$(OUTDIR)\test\function\formatter\$(NULL)" mkdir $(OUTDIR)\test\function\formatter
    if not exist "$(OUTDIR)\test\function\handler\$(NULL)" mkdir $(OUTDIR)\test\function\handler
    if not exist "$(OUTDIR)\test\function\logger\$(NULL)" mkdir $(OUTDIR)\test\function\logger
    if not exist "$(OUTDIR)\test\function\output\$(NULL)" mkdir $(OUTDIR)\test\function\output
    if not exist "$(OUTDIR)\test\function\utility\$(NULL)" mkdir $(OUTDIR)\test\function\utility
    if not exist "$(OUTDIR)\test\function\value\$(NULL)" mkdir $(OUTDIR)\test\function\value
    if not exist "$(OUTDIR)\test\helper\$(NULL)" mkdir $(OUTDIR)\test\helper
    

    
# build library
$(OUTDIR)\stumpless.dll: $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) $(dlllflags) -nologo -out:$(OUTDIR)\stumpless.dll /DEF:$(BASEDIR)\stumpless.def $(STUMPLESSOBJECTS)    


# library object files
$(OUTDIR)\src\adapter.obj: $(OUTDIR) $(SRCDIR)\adapter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\adapter.c
    
$(OUTDIR)\src\adapter\base.obj: $(SRCDIR)\adapter\base.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\adapter\ /Fd$(OUTDIR)\src\ $(SRCDIR)\adapter\base.c
    
$(OUTDIR)\src\adapter\initializer.obj: $(SRCDIR)\adapter\initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\adapter\ /Fd$(OUTDIR)\src\ $(SRCDIR)\adapter\initializer.c
    
$(OUTDIR)\src\boolean.obj: $(SRCDIR)\boolean.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\boolean.c
    
$(OUTDIR)\src\comparator.obj: $(SRCDIR)\comparator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\comparator.c
    
$(OUTDIR)\src\comparator\base.obj: $(SRCDIR)\comparator\base.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\comparator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\comparator\base.c
    
$(OUTDIR)\src\comparator\initializer.obj: $(SRCDIR)\comparator\initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\comparator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\comparator\initializer.c
    
$(OUTDIR)\src\configuration.obj: $(SRCDIR)\configuration.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\configuration.c
    
$(OUTDIR)\src\container\dictionary.obj: $(SRCDIR)\container\dictionary.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\dictionary.c
    
$(OUTDIR)\src\container\dictionary\const_iterator.obj: $(SRCDIR)\container\dictionary\const_iterator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\dictionary\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\dictionary\const_iterator.c
    
$(OUTDIR)\src\container\list.obj: $(SRCDIR)\container\list.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list.c
    
$(OUTDIR)\src\container\list\adapter.obj: $(SRCDIR)\container\list\adapter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\adapter.c
    
$(OUTDIR)\src\container\list\comparator.obj: $(SRCDIR)\container\list\comparator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\comparator.c
    
$(OUTDIR)\src\container\list\const_iterator.obj: $(SRCDIR)\container\list\const_iterator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_iterator.c
    
$(OUTDIR)\src\container\list\const_iterator\adapter.obj: $(SRCDIR)\container\list\const_iterator\adapter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_iterator\adapter.c
    
$(OUTDIR)\src\container\list\const_iterator\comparator.obj: $(SRCDIR)\container\list\const_iterator\comparator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_iterator\comparator.c
    
$(OUTDIR)\src\container\list\const_iterator\filter.obj: $(SRCDIR)\container\list\const_iterator\filter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_iterator\filter.c
    
$(OUTDIR)\src\container\list\const_iterator\formatter.obj: $(SRCDIR)\container\list\const_iterator\formatter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_iterator\formatter.c
    
$(OUTDIR)\src\container\list\const_iterator\handler.obj: $(SRCDIR)\container\list\const_iterator\handler.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_iterator\handler.c
    
$(OUTDIR)\src\container\list\const_iterator\target.obj: $(SRCDIR)\container\list\const_iterator\target.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_iterator\target.c
    
$(OUTDIR)\src\container\list\const_iterator\value.obj: $(SRCDIR)\container\list\const_iterator\value.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_iterator\value.c
    
$(OUTDIR)\src\container\list\const_reverse_iterator.obj: $(SRCDIR)\container\list\const_reverse_iterator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_reverse_iterator.c
    
$(OUTDIR)\src\container\list\const_reverse_iterator\adapter.obj: $(SRCDIR)\container\list\const_reverse_iterator\adapter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_reverse_iterator\adapter.c
    
$(OUTDIR)\src\container\list\const_reverse_iterator\comparator.obj: $(SRCDIR)\container\list\const_reverse_iterator\comparator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_reverse_iterator\comparator.c
    
$(OUTDIR)\src\container\list\const_reverse_iterator\filter.obj: $(SRCDIR)\container\list\const_reverse_iterator\filter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_reverse_iterator\filter.c
    
$(OUTDIR)\src\container\list\const_reverse_iterator\formatter.obj: $(SRCDIR)\container\list\const_reverse_iterator\formatter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_reverse_iterator\formatter.c
    
$(OUTDIR)\src\container\list\const_reverse_iterator\handler.obj: $(SRCDIR)\container\list\const_reverse_iterator\handler.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_reverse_iterator\handler.c
    
$(OUTDIR)\src\container\list\const_reverse_iterator\target.obj: $(SRCDIR)\container\list\const_reverse_iterator\target.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_reverse_iterator\target.c
    
$(OUTDIR)\src\container\list\const_reverse_iterator\value.obj: $(SRCDIR)\container\list\const_reverse_iterator\value.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_reverse_iterator\value.c
    
$(OUTDIR)\src\container\list\filter.obj: $(SRCDIR)\container\list\filter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\filter.c
    
$(OUTDIR)\src\container\list\formatter.obj: $(SRCDIR)\container\list\formatter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\formatter.c
    
$(OUTDIR)\src\container\list\handler.obj: $(SRCDIR)\container\list\handler.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\handler.c
    
$(OUTDIR)\src\container\list\iterator.obj: $(SRCDIR)\container\list\iterator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\iterator.c
    
$(OUTDIR)\src\container\list\iterator\adapter.obj: $(SRCDIR)\container\list\iterator\adapter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\iterator\adapter.c
    
$(OUTDIR)\src\container\list\iterator\comparator.obj: $(SRCDIR)\container\list\iterator\comparator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\iterator\comparator.c
    
$(OUTDIR)\src\container\list\iterator\filter.obj: $(SRCDIR)\container\list\iterator\filter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\iterator\filter.c
    
$(OUTDIR)\src\container\list\iterator\formatter.obj: $(SRCDIR)\container\list\iterator\formatter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\iterator\formatter.c
    
$(OUTDIR)\src\container\list\iterator\handler.obj: $(SRCDIR)\container\list\iterator\handler.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\iterator\handler.c
    
$(OUTDIR)\src\container\list\iterator\target.obj: $(SRCDIR)\container\list\iterator\target.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\iterator\target.c
    
$(OUTDIR)\src\container\list\iterator\value.obj: $(SRCDIR)\container\list\iterator\value.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\iterator\value.c
    
$(OUTDIR)\src\container\list\reverse_iterator.obj: $(SRCDIR)\container\list\reverse_iterator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\reverse_iterator.c
    
$(OUTDIR)\src\container\list\reverse_iterator\adapter.obj: $(SRCDIR)\container\list\reverse_iterator\adapter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\reverse_iterator\adapter.c
    
$(OUTDIR)\src\container\list\reverse_iterator\comparator.obj: $(SRCDIR)\container\list\reverse_iterator\comparator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\reverse_iterator\comparator.c
    
$(OUTDIR)\src\container\list\reverse_iterator\filter.obj: $(SRCDIR)\container\list\reverse_iterator\filter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\reverse_iterator\filter.c
    
$(OUTDIR)\src\container\list\reverse_iterator\formatter.obj: $(SRCDIR)\container\list\reverse_iterator\formatter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\reverse_iterator\formatter.c
    
$(OUTDIR)\src\container\list\reverse_iterator\handler.obj: $(SRCDIR)\container\list\reverse_iterator\handler.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\reverse_iterator\handler.c
    
$(OUTDIR)\src\container\list\reverse_iterator\target.obj: $(SRCDIR)\container\list\reverse_iterator\target.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\reverse_iterator\target.c
    
$(OUTDIR)\src\container\list\reverse_iterator\value.obj: $(SRCDIR)\container\list\reverse_iterator\value.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\reverse_iterator\value.c
    
$(OUTDIR)\src\container\list\target.obj: $(SRCDIR)\container\list\target.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\target.c
    
$(OUTDIR)\src\container\list\value.obj: $(SRCDIR)\container\list\value.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\value.c
    
$(OUTDIR)\src\container\queue.obj: $(SRCDIR)\container\queue.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\queue.c
    
$(OUTDIR)\src\container\stack.obj: $(SRCDIR)\container\stack.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\stack.c
    
$(OUTDIR)\src\container\tree.obj: $(SRCDIR)\container\tree.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\container\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\tree.c
    
$(OUTDIR)\src\event.obj: $(SRCDIR)\event.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\event.c
    
$(OUTDIR)\src\event_attribute.obj: $(SRCDIR)\event_attribute.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\event_attribute.c
    
$(OUTDIR)\src\exception.obj: $(SRCDIR)\exception.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\exception.c
    
$(OUTDIR)\src\exception\handler.obj: $(SRCDIR)\exception\handler.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\exception\ /Fd$(OUTDIR)\src\ $(SRCDIR)\exception\handler.c
    
$(OUTDIR)\src\filter.obj: $(SRCDIR)\filter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\filter.c
    
$(OUTDIR)\src\filter\base.obj: $(SRCDIR)\filter\base.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\filter\ /Fd$(OUTDIR)\src\ $(SRCDIR)\filter\base.c
    
$(OUTDIR)\src\filter\initializer.obj: $(SRCDIR)\filter\initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\filter\ /Fd$(OUTDIR)\src\ $(SRCDIR)\filter\initializer.c
    
$(OUTDIR)\src\formatter.obj: $(SRCDIR)\formatter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\formatter.c
    
$(OUTDIR)\src\formatter\csv.obj: $(SRCDIR)\formatter\csv.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\formatter\ /Fd$(OUTDIR)\src\ $(SRCDIR)\formatter\csv.c
    
$(OUTDIR)\src\formatter\initializer.obj: $(SRCDIR)\formatter\initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\formatter\ /Fd$(OUTDIR)\src\ $(SRCDIR)\formatter\initializer.c
    
$(OUTDIR)\src\formatter\text.obj: $(SRCDIR)\formatter\text.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\formatter\ /Fd$(OUTDIR)\src\ $(SRCDIR)\formatter\text.c
    
$(OUTDIR)\src\handler.obj: $(SRCDIR)\handler.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\handler.c
    
$(OUTDIR)\src\handler\initializer.obj: $(SRCDIR)\handler\initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\handler\ /Fd$(OUTDIR)\src\ $(SRCDIR)\handler\initializer.c
    
$(OUTDIR)\src\handler\stream.obj: $(SRCDIR)\handler\stream.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\handler\ /Fd$(OUTDIR)\src\ $(SRCDIR)\handler\stream.c
    
$(OUTDIR)\src\level.obj: $(SRCDIR)\level.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\level.c
    
$(OUTDIR)\src\level\initializer.obj: $(SRCDIR)\level\initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\level\ /Fd$(OUTDIR)\src\ $(SRCDIR)\level\initializer.c
    
$(OUTDIR)\src\logger.obj: $(SRCDIR)\logger.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\logger.c
    
$(OUTDIR)\src\logger\getter.obj: $(SRCDIR)\logger\getter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\logger\ /Fd$(OUTDIR)\src\ $(SRCDIR)\logger\getter.c
    
$(OUTDIR)\src\logger\log.obj: $(SRCDIR)\logger\log.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\logger\ /Fd$(OUTDIR)\src\ $(SRCDIR)\logger\log.c
    
$(OUTDIR)\src\logger\sender.obj: $(SRCDIR)\logger\sender.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\logger\ /Fd$(OUTDIR)\src\ $(SRCDIR)\logger\sender.c
    
$(OUTDIR)\src\output.obj: $(SRCDIR)\output.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\output.c
    
$(OUTDIR)\src\output\profile.obj: $(SRCDIR)\output\profile.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\output\ /Fd$(OUTDIR)\src\ $(SRCDIR)\output\profile.c
    
$(OUTDIR)\src\output\profile_initializer.obj: $(SRCDIR)\output\profile_initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\output\ /Fd$(OUTDIR)\src\ $(SRCDIR)\output\profile_initializer.c
    
$(OUTDIR)\src\private\event\initializer.obj: $(SRCDIR)\private\event\initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\private\event\ /Fd$(OUTDIR)\src\ $(SRCDIR)\private\event\initializer.c
    
$(OUTDIR)\src\private\exception\initializer.obj: $(SRCDIR)\private\exception\initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\private\exception\ /Fd$(OUTDIR)\src\ $(SRCDIR)\private\exception\initializer.c
    
$(OUTDIR)\src\private\exception\thrower.obj: $(SRCDIR)\private\exception\thrower.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\private\exception\ /Fd$(OUTDIR)\src\ $(SRCDIR)\private\exception\thrower.c
    
$(OUTDIR)\src\private\utility\string.obj: $(SRCDIR)\private\utility\string.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\private\utility\ /Fd$(OUTDIR)\src\ $(SRCDIR)\private\utility\string.c
    
$(OUTDIR)\src\record.obj: $(SRCDIR)\record.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\record.c
    
$(OUTDIR)\src\record_attribute.obj: $(SRCDIR)\record_attribute.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\record_attribute.c
    
$(OUTDIR)\src\target.obj: $(SRCDIR)\target.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\target.c
    
$(OUTDIR)\src\value.obj: $(SRCDIR)\value.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\value.c
    
$(OUTDIR)\src\value\constructor.obj: $(SRCDIR)\value\constructor.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\value\ /Fd$(OUTDIR)\src\ $(SRCDIR)\value\constructor.c
    
$(OUTDIR)\src\value\profile.obj: $(SRCDIR)\value\profile.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\value\ /Fd$(OUTDIR)\src\ $(SRCDIR)\value\profile.c
    
$(OUTDIR)\src\value\profile_initializer.obj: $(SRCDIR)\value\profile_initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\src\value\ /Fd$(OUTDIR)\src\ $(SRCDIR)\value\profile_initializer.c
    

# run tests
check: $(OUTDIR) \
       $(STUMPLESSOBJECTS) \
       $(OUTDIR)\stumpless.dll \
       $(OUTDIR)\test\function\adapter_suite.exe \
       $(OUTDIR)\test\function\boolean_suite.exe \
       $(OUTDIR)\test\function\comparator_suite.exe \
       $(OUTDIR)\test\function\comparator\base_suite.exe \
       $(OUTDIR)\test\function\configuration_suite.exe \
       $(OUTDIR)\test\function\container\dictionary_suite.exe \
       $(OUTDIR)\test\function\container\dictionary\const_iterator_suite.exe \
       $(OUTDIR)\test\function\container\list_suite.exe \
       $(OUTDIR)\test\function\container\list\adapter_suite.exe \
       $(OUTDIR)\test\function\container\list\comparator_suite.exe \
       $(OUTDIR)\test\function\container\list\const_iterator_suite.exe \
       $(OUTDIR)\test\function\container\list\filter_suite.exe \
       $(OUTDIR)\test\function\container\list\formatter_suite.exe \
       $(OUTDIR)\test\function\container\list\handler_suite.exe \
       $(OUTDIR)\test\function\container\list\iterator_suite.exe \
       $(OUTDIR)\test\function\container\list\reverse_iterator_suite.exe \
       $(OUTDIR)\test\function\container\list\value_suite.exe \
       $(OUTDIR)\test\function\container\queue_suite.exe \
       $(OUTDIR)\test\function\container\stack_suite.exe \
       $(OUTDIR)\test\function\container\tree_suite.exe \
       $(OUTDIR)\test\function\event_suite.exe \
       $(OUTDIR)\test\function\exception_suite.exe \
       $(OUTDIR)\test\function\exception\initializer_suite.exe \
       $(OUTDIR)\test\function\exception\handler_suite.exe \
       $(OUTDIR)\test\function\exception\thrower_suite.exe \
       $(OUTDIR)\test\function\filter_suite.exe \
       $(OUTDIR)\test\function\filter\base_suite.exe \
       $(OUTDIR)\test\function\formatter_suite.exe \
       $(OUTDIR)\test\function\formatter\text_suite.exe \
       $(OUTDIR)\test\function\handler_suite.exe \
       $(OUTDIR)\test\function\handler\stream_suite.exe \
       $(OUTDIR)\test\function\level_suite.exe \
       $(OUTDIR)\test\function\logger_suite.exe \
       $(OUTDIR)\test\function\logger\log_suite.exe \
       $(OUTDIR)\test\function\output_suite.exe \
       $(OUTDIR)\test\function\output\profile_suite.exe \
       $(OUTDIR)\test\function\output\profile_initializer_suite.exe \
       $(OUTDIR)\test\function\record_attribute_suite.exe \
       $(OUTDIR)\test\function\record_suite.exe \
       $(OUTDIR)\test\function\target_suite.exe \
       $(OUTDIR)\test\function\utility\string_suite.exe \
       $(OUTDIR)\test\function\value_suite.exe \
       $(OUTDIR)\test\function\value\constructor_suite.exe \
       $(OUTDIR)\test\function\value\profile_suite.exe \
       $(OUTDIR)\test\function\value\profile_initializer_suite.exe
    cd $(OUTDIR)
    $(OUTDIR)\test\function\adapter_suite.exe > $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\boolean_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\comparator_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\comparator\base_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\configuration_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\container\dictionary_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\container\dictionary\const_iterator_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\container\list_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\container\list\adapter_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\container\list\comparator_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\container\list\const_iterator_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\container\list\filter_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\container\list\formatter_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\container\list\handler_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\container\list\iterator_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\container\list\reverse_iterator_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\container\list\value_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\container\queue_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\container\stack_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\container\tree_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\event_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\exception_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\exception\initializer_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\exception\handler_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\exception\thrower_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\filter_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\filter\base_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\formatter_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\formatter\text_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\handler_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\handler\stream_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\level_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\logger_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\logger\log_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\output_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\output\profile_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\output\profile_initializer_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\record_attribute_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\record_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\target_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\utility\string_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\value_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\value\constructor_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\value\profile_suite.exe >> $(OUTDIR)\test-suite.log
    $(OUTDIR)\test\function\value\profile_initializer_suite.exe >> $(OUTDIR)\test-suite.log


# executable files
$(OUTDIR)\test\function\adapter_suite.exe: $(OUTDIR)\test\function\adapter_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\adapter_suite.exe $(OUTDIR)\test\function\adapter_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\boolean_suite.exe: $(OUTDIR)\test\function\boolean_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\boolean_suite.exe $(OUTDIR)\test\function\boolean_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\comparator_suite.exe: $(OUTDIR)\test\function\comparator_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\comparator_suite.exe $(OUTDIR)\test\function\comparator_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\comparator\base_suite.exe: $(OUTDIR)\test\function\comparator\base_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\comparator\base_suite.exe $(OUTDIR)\test\function\comparator\base_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\configuration_suite.exe: $(OUTDIR)\test\function\configuration_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\configuration_suite.exe $(OUTDIR)\test\function\configuration_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\container\dictionary_suite.exe: $(OUTDIR)\test\function\container\dictionary_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\container\dictionary_suite.exe $(OUTDIR)\test\function\container\dictionary_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\container\dictionary\const_iterator_suite.exe: $(OUTDIR)\test\function\container\dictionary\const_iterator_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\container\dictionary\const_iterator_suite.exe $(OUTDIR)\test\function\container\dictionary\const_iterator_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\container\list_suite.exe: $(OUTDIR)\test\function\container\list_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\container\list_suite.exe $(OUTDIR)\test\function\container\list_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\container\list\adapter_suite.exe: $(OUTDIR)\test\function\container\list\adapter_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\container\list\adapter_suite.exe $(OUTDIR)\test\function\container\list\adapter_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\container\list\comparator_suite.exe: $(OUTDIR)\test\function\container\list\comparator_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\container\list\comparator_suite.exe $(OUTDIR)\test\function\container\list\comparator_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\container\list\const_iterator_suite.exe: $(OUTDIR)\test\function\container\list\const_iterator_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\container\list\const_iterator_suite.exe $(OUTDIR)\test\function\container\list\const_iterator_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\container\list\filter_suite.exe: $(OUTDIR)\test\function\container\list\filter_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\container\list\filter_suite.exe $(OUTDIR)\test\function\container\list\filter_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\container\list\formatter_suite.exe: $(OUTDIR)\test\function\container\list\formatter_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\container\list\formatter_suite.exe $(OUTDIR)\test\function\container\list\formatter_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\container\list\handler_suite.exe: $(OUTDIR)\test\function\container\list\handler_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\container\list\handler_suite.exe $(OUTDIR)\test\function\container\list\handler_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\container\list\iterator_suite.exe: $(OUTDIR)\test\function\container\list\iterator_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\container\list\iterator_suite.exe $(OUTDIR)\test\function\container\list\iterator_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\container\list\reverse_iterator_suite.exe: $(OUTDIR)\test\function\container\list\reverse_iterator_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\container\list\reverse_iterator_suite.exe $(OUTDIR)\test\function\container\list\reverse_iterator_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\container\list\value_suite.exe: $(OUTDIR)\test\function\container\list\value_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\container\list\value_suite.exe $(OUTDIR)\test\function\container\list\value_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\container\queue_suite.exe: $(OUTDIR)\test\function\container\queue_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\container\queue_suite.exe $(OUTDIR)\test\function\container\queue_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\container\stack_suite.exe: $(OUTDIR)\test\function\container\stack_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\container\stack_suite.exe $(OUTDIR)\test\function\container\stack_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\container\tree_suite.exe: $(OUTDIR)\test\function\container\tree_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\container\tree_suite.exe $(OUTDIR)\test\function\container\tree_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\event_suite.exe: $(OUTDIR)\test\function\event_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\event_suite.exe $(OUTDIR)\test\function\event_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\exception_suite.exe: $(OUTDIR)\test\function\exception_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\exception_suite.exe $(OUTDIR)\test\function\exception_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\exception\initializer_suite.exe: $(OUTDIR)\test\function\exception\initializer_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\exception\initializer_suite.exe $(OUTDIR)\test\function\exception\initializer_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\exception\handler_suite.exe: $(OUTDIR)\test\function\exception\handler_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\exception\handler_suite.exe $(OUTDIR)\test\function\exception\handler_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\exception\thrower_suite.exe: $(OUTDIR)\test\function\exception\thrower_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\exception\thrower_suite.exe $(OUTDIR)\test\function\exception\thrower_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\initializer_suite.exe: $(OUTDIR)\test\function\exception\initializer_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\exception_suite.exe $(OUTDIR)\test\function\exception\initializer_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\filter_suite.exe: $(OUTDIR)\test\function\filter_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\filter_suite.exe $(OUTDIR)\test\function\filter_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\filter\base_suite.exe: $(OUTDIR)\test\function\filter\base_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\filter\base_suite.exe $(OUTDIR)\test\function\filter\base_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\formatter_suite.exe: $(OUTDIR)\test\function\formatter_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\formatter_suite.exe $(OUTDIR)\test\function\formatter_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\formatter\text_suite.exe: $(OUTDIR)\test\function\formatter\text_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\formatter\text_suite.exe $(OUTDIR)\test\function\formatter\text_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\handler_suite.exe: $(OUTDIR)\test\function\handler_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\handler_suite.exe $(OUTDIR)\test\function\handler_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\handler\stream_suite.exe: $(OUTDIR)\test\function\handler\stream_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\handler\stream_suite.exe $(OUTDIR)\test\function\handler\stream_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\level_suite.exe: $(OUTDIR)\test\function\level_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\level_suite.exe $(OUTDIR)\test\function\level_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\logger_suite.exe: $(OUTDIR)\test\function\logger_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\logger_suite.exe $(OUTDIR)\test\function\logger_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\logger\log_suite.exe: $(OUTDIR)\test\function\logger\log_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\logger\log_suite.exe $(OUTDIR)\test\function\logger\log_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\output_suite.exe: $(OUTDIR)\test\function\output_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\output_suite.exe $(OUTDIR)\test\function\output_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\output\profile_suite.exe: $(OUTDIR)\test\function\output\profile_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\output\profile_suite.exe $(OUTDIR)\test\function\output\profile_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\output\profile_initializer_suite.exe: $(OUTDIR)\test\function\output\profile_initializer_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\output\profile_initializer_suite.exe $(OUTDIR)\test\function\output\profile_initializer_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\record_attribute_suite.exe: $(OUTDIR)\test\function\record_attribute_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\record_attribute_suite.exe $(OUTDIR)\test\function\record_attribute_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\record_suite.exe: $(OUTDIR)\test\function\record_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\record_suite.exe $(OUTDIR)\test\function\record_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\string_helper_suite.exe: $(OUTDIR)\test\function\string_helper_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\string_helper_suite.exe $(OUTDIR)\test\function\string_helper_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\target_suite.exe: $(OUTDIR)\test\function\target_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\target_suite.exe $(OUTDIR)\test\function\target_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\utility\string_suite.exe: $(OUTDIR)\test\function\utility\string_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\utility\string_suite.exe $(OUTDIR)\test\function\utility\string_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\value_suite.exe: $(OUTDIR)\test\function\value_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\value_suite.exe $(OUTDIR)\test\function\value_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\value\constructor_suite.exe: $(OUTDIR)\test\function\value\constructor_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\value\constructor_suite.exe $(OUTDIR)\test\function\value\constructor_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\value\profile_suite.exe: $(OUTDIR)\test\function\value\profile_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\value\profile_suite.exe $(OUTDIR)\test\function\value\profile_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
$(OUTDIR)\test\function\value\profile_initializer_suite.exe: $(OUTDIR)\test\function\value\profile_initializer_suite.obj $(OUTDIR)\helper.dll $(STUMPLESSOBJECTS)
    $(link) $(linkdebug) -nologo -out:$(OUTDIR)\test\function\value\profile_initializer_suite.exe $(OUTDIR)\test\function\value\profile_initializer_suite.obj $(OUTDIR)\helper.lib $(STUMPLESSOBJECTS)
    
    
# test object files
$(OUTDIR)\test\function\adapter_suite.obj: $(TESTDIR)\function\adapter_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\adapter_suite.c
    
$(OUTDIR)\test\function\boolean_suite.obj: $(TESTDIR)\function\boolean_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\boolean_suite.c
    
$(OUTDIR)\test\function\comparator_suite.obj: $(TESTDIR)\function\comparator_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\comparator_suite.c
    
$(OUTDIR)\test\function\comparator\base_suite.obj: $(TESTDIR)\function\comparator\base_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\comparator\ /Fd$(OUTDIR)\test\function\comparator\ $(TESTDIR)\function\comparator\base_suite.c
    
$(OUTDIR)\test\function\configuration_suite.obj: $(TESTDIR)\function\configuration_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\configuration_suite.c
    
$(OUTDIR)\test\function\container\dictionary_suite.obj: $(TESTDIR)\function\container\dictionary_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\container\ /Fd$(OUTDIR)\test\function\container\ $(TESTDIR)\function\container\dictionary_suite.c
    
$(OUTDIR)\test\function\container\dictionary\const_iterator_suite.obj: $(TESTDIR)\function\container\dictionary\const_iterator_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\container\dictionary\ /Fd$(OUTDIR)\test\function\container\dictionary\ $(TESTDIR)\function\container\dictionary\const_iterator_suite.c
    
$(OUTDIR)\test\function\container\list_suite.obj: $(TESTDIR)\function\container\list_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\container\ /Fd$(OUTDIR)\test\function\container\ $(TESTDIR)\function\container\list_suite.c
    
$(OUTDIR)\test\function\container\list\adapter_suite.obj: $(TESTDIR)\function\container\list\adapter_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\container\list\ /Fd$(OUTDIR)\test\function\container\list\ $(TESTDIR)\function\container\list\adapter_suite.c
    
$(OUTDIR)\test\function\container\list\comparator_suite.obj: $(TESTDIR)\function\container\list\comparator_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\container\list\ /Fd$(OUTDIR)\test\function\container\list\ $(TESTDIR)\function\container\list\comparator_suite.c
    
$(OUTDIR)\test\function\container\list\const_iterator_suite.obj: $(TESTDIR)\function\container\list\const_iterator_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\container\list\ /Fd$(OUTDIR)\test\function\container\list\ $(TESTDIR)\function\container\list\const_iterator_suite.c
    
$(OUTDIR)\test\function\container\list\filter_suite.obj: $(TESTDIR)\function\container\list\filter_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\container\list\ /Fd$(OUTDIR)\test\function\container\list\ $(TESTDIR)\function\container\list\filter_suite.c
    
$(OUTDIR)\test\function\container\list\formatter_suite.obj: $(TESTDIR)\function\container\list\formatter_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\container\list\ /Fd$(OUTDIR)\test\function\container\list\ $(TESTDIR)\function\container\list\formatter_suite.c
    
$(OUTDIR)\test\function\container\list\handler_suite.obj: $(TESTDIR)\function\container\list\handler_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\container\list\ /Fd$(OUTDIR)\test\function\container\list\ $(TESTDIR)\function\container\list\handler_suite.c
    
$(OUTDIR)\test\function\container\list\iterator_suite.obj: $(TESTDIR)\function\container\list\iterator_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\container\list\ /Fd$(OUTDIR)\test\function\container\list\ $(TESTDIR)\function\container\list\iterator_suite.c
    
$(OUTDIR)\test\function\container\list\reverse_iterator_suite.obj: $(TESTDIR)\function\container\list\reverse_iterator_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\container\list\ /Fd$(OUTDIR)\test\function\container\list\ $(TESTDIR)\function\container\list\reverse_iterator_suite.c
    
$(OUTDIR)\test\function\container\list\value_suite.obj: $(TESTDIR)\function\container\list\value_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\container\list\ /Fd$(OUTDIR)\test\function\container\list\ $(TESTDIR)\function\container\list\value_suite.c
    
$(OUTDIR)\test\function\container\queue_suite.obj: $(TESTDIR)\function\container\queue_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\container\ /Fd$(OUTDIR)\test\function\container\ $(TESTDIR)\function\container\queue_suite.c
    
$(OUTDIR)\test\function\container\stack_suite.obj: $(TESTDIR)\function\container\stack_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\container\ /Fd$(OUTDIR)\test\function\container\ $(TESTDIR)\function\container\stack_suite.c
    
$(OUTDIR)\test\function\container\tree_suite.obj: $(TESTDIR)\function\container\tree_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\container\ /Fd$(OUTDIR)\test\function\container\ $(TESTDIR)\function\container\tree_suite.c
    
$(OUTDIR)\test\function\event_suite.obj: $(TESTDIR)\function\event_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\event_suite.c
    
$(OUTDIR)\test\function\exception_suite.obj: $(TESTDIR)\function\exception_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\exception_suite.c
    
$(OUTDIR)\test\function\exception\initializer_suite.obj: $(TESTDIR)\function\exception\initializer_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\exception\ /Fd$(OUTDIR)\test\function\exception\ $(TESTDIR)\function\exception\initializer_suite.c
    
$(OUTDIR)\test\function\exception\handler_suite.obj: $(TESTDIR)\function\exception\handler_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\exception\ /Fd$(OUTDIR)\test\function\exception\ $(TESTDIR)\function\exception\handler_suite.c
    
$(OUTDIR)\test\function\exception\thrower_suite.obj: $(TESTDIR)\function\exception\thrower_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\exception\ /Fd$(OUTDIR)\test\function\exception\ $(TESTDIR)\function\exception\thrower_suite.c
    
$(OUTDIR)\test\function\filter_suite.obj: $(TESTDIR)\function\filter_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\filter_suite.c
    
$(OUTDIR)\test\function\filter\base_suite.obj: $(TESTDIR)\function\filter\base_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\filter\ /Fd$(OUTDIR)\test\function\filter\ $(TESTDIR)\function\filter\base_suite.c
    
$(OUTDIR)\test\function\formatter_suite.obj: $(TESTDIR)\function\formatter_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\formatter_suite.c
    
$(OUTDIR)\test\function\formatter\text_suite.obj: $(TESTDIR)\function\formatter\text_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\formatter\ /Fd$(OUTDIR)\test\function\formatter\ $(TESTDIR)\function\formatter\text_suite.c
    
$(OUTDIR)\test\function\handler_suite.obj: $(TESTDIR)\function\handler_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\handler_suite.c
    
$(OUTDIR)\test\function\handler\stream_suite.obj: $(TESTDIR)\function\handler\stream_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\handler\ /Fd$(OUTDIR)\test\function\handler\ $(TESTDIR)\function\handler\stream_suite.c
    
$(OUTDIR)\test\function\level_suite.obj: $(TESTDIR)\function\level_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\level_suite.c
    
$(OUTDIR)\test\function\logger_suite.obj: $(TESTDIR)\function\logger_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\logger_suite.c
    
$(OUTDIR)\test\function\logger\log_suite.obj: $(TESTDIR)\function\logger\log_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\logger\ /Fd$(OUTDIR)\test\function\logger\ $(TESTDIR)\function\logger\log_suite.c
    
$(OUTDIR)\test\function\output_suite.obj: $(TESTDIR)\function\output_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\output_suite.c
    
$(OUTDIR)\test\function\output\profile_suite.obj: $(TESTDIR)\function\output\profile_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\output\ /Fd$(OUTDIR)\test\function\output\ $(TESTDIR)\function\output\profile_suite.c
    
$(OUTDIR)\test\function\output\profile_initializer_suite.obj: $(TESTDIR)\function\output\profile_initializer_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\output\ /Fd$(OUTDIR)\test\function\output\ $(TESTDIR)\function\output\profile_initializer_suite.c
    
$(OUTDIR)\test\function\record_attribute_suite.obj: $(TESTDIR)\function\record_attribute_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\record_attribute_suite.c
    
$(OUTDIR)\test\function\record_suite.obj: $(TESTDIR)\function\record_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\record_suite.c
    
$(OUTDIR)\test\function\target_suite.obj: $(TESTDIR)\function\target_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\target_suite.c
    
$(OUTDIR)\test\function\utility\string_suite.obj: $(TESTDIR)\function\utility\string_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\utility\ /Fd$(OUTDIR)\test\function\utility\ $(TESTDIR)\function\utility\string_suite.c
    
$(OUTDIR)\test\function\value_suite.obj: $(TESTDIR)\function\value_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\value_suite.c
    
$(OUTDIR)\test\function\value\constructor_suite.obj: $(TESTDIR)\function\value\constructor_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\value\ /Fd$(OUTDIR)\test\function\value $(TESTDIR)\function\value\constructor_suite.c
    
$(OUTDIR)\test\function\value\profile_suite.obj: $(TESTDIR)\function\value\profile_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\value\ /Fd$(OUTDIR)\test\function\value $(TESTDIR)\function\value\profile_suite.c
    
$(OUTDIR)\test\function\value\profile_initializer_suite.obj: $(TESTDIR)\function\value\profile_initializer_suite.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\function\value\ /Fd$(OUTDIR)\test\function\value $(TESTDIR)\function\value\profile_initializer_suite.c


# build test helper library
$(OUTDIR)\helper.dll: $(OUTDIR)\stumpless.dll $(OUTDIR)\test\helper\builder.obj $(OUTDIR)\test\helper\fixture.obj $(OUTDIR)\test\helper\log.obj
    $(link) $(linkdebug) $(dlllflags) -nologo -out:$(OUTDIR)\helper.dll /DEF:$(BASEDIR)\test\helper.def $(OUTDIR)\stumpless.lib $(OUTDIR)\test\helper\builder.obj $(OUTDIR)\test\helper\fixture.obj $(OUTDIR)\test\helper\log.obj  
    
    
# test helper library object files
$(OUTDIR)\test\helper\builder.obj: $(TESTDIR)\helper\builder.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\helper\ /Fd$(OUTDIR)\test\helper\ $(TESTDIR)\helper\builder.c

$(OUTDIR)\test\helper\fixture.obj: $(TESTDIR)\helper\fixture.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\helper\ /Fd$(OUTDIR)\test\helper\ $(TESTDIR)\helper\fixture.c

$(OUTDIR)\test\helper\log.obj: $(TESTDIR)\helper\log.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(STUMPLESSFLAGS) /I $(INCDIR) /Fo$(OUTDIR)\test\helper\ /Fd$(OUTDIR)\test\helper\ $(TESTDIR)\helper\log.c
    
    
clean:
    $(CLEANUP)