[++ AutoGen5 Template ++]
# Global variables.
lo2o="s/\\.lo\$/.${objext}/"
o2lo="s/\\.${objext}\$/.lo/"
magic="%%%MAGIC variable%%%"
mkdir="mkdir"
mv="mv -f"
rm="rm -f"

# Sed substitution that helps us do robust quoting.  It backslashifies
# metacharacters that are still active within double-quoted strings.
Xsed='sed -e 1s/^X//'
sed_quote_subst='s/\([\\`\\"$\\\\]\)/\\\1/g'
SP2NL='tr \040 \012'
NL2SP='tr \015\012 \040\040'

# NLS nuisances.
# Only set LANG and LC_ALL to C if already set.
# These must not be set unconditionally because not all systems understand
# e.g. LANG=C (notably SCO).
# We save the old values to restore during execute mode.
if test "${LC_ALL+set}" = set; then
  save_LC_ALL="$LC_ALL"; LC_ALL=C; export LC_ALL
fi
if test "${LANG+set}" = set; then
  save_LANG="$LANG"; LANG=C; export LANG
fi
