Small wrapper command to run commands as the special zope user
--------------------------------------------------------------

The program relies on being installed as owned by zope and with the
setuid bit set.  It checksm when runm to make sure that the effective
user is zope and that the original user is in the zope group.
