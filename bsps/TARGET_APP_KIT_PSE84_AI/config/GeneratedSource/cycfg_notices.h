 




























#if !defined(CYCFG_NOTICES_H)
#define CYCFG_NOTICES_H

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

#if defined(CY_SUPPORTS_DEVICE_VALIDATION)
#if !defined(PSE846GPS2DBZC4A)
#error "Unexpected MPN; expected DEVICE:=PSE846GPS2DBZC4A. There may be an inconsistency between the *.modus file and the makefile target configuration device sets."
#endif /* !defined(PSE846GPS2DBZC4A) */
#endif /* defined(CY_SUPPORTS_DEVICE_VALIDATION) */

#if defined(CY_SUPPORTS_COMPLETE_DEVICE_VALIDATION)
#if !defined(PSE846GPS2DBZC4A)
#error "Unexpected MPN; expected DEVICE:=PSE846GPS2DBZC4A, ADDITIONAL_DEVICES:=CYW55513IUBG. There may be an inconsistency between the *.modus file and the makefile target configuration device sets."
#endif /* !defined(PSE846GPS2DBZC4A) */
#if !defined(CYW55513IUBG)
#error "Unexpected MPN; expected DEVICE:=PSE846GPS2DBZC4A, ADDITIONAL_DEVICES:=CYW55513IUBG. There may be an inconsistency between the *.modus file and the makefile target configuration device sets."
#endif /* !defined(CYW55513IUBG) */
#endif /* defined(CY_SUPPORTS_COMPLETE_DEVICE_VALIDATION) */

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* CYCFG_NOTICES_H */
