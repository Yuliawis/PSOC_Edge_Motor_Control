 



























#if !defined(CYCFG_PROTECTION_H)
#define CYCFG_PROTECTION_H

#include "cycfg_notices.h"

#if defined (COMPONENT_SECURE_DEVICE) && defined(COMPONENT_MW_MTB_SRF) && !defined(CY_SRF_DISABLE)
#include "mtb_srf.h"
#endif /* defined (COMPONENT_SECURE_DEVICE) && defined(COMPONENT_MW_MTB_SRF) && !defined(CY_SRF_DISABLE) */

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

#define vres_0_protection_0_ENABLED 1U

#if defined (COMPONENT_SECURE_DEVICE) && defined(COMPONENT_MW_MTB_SRF) && !defined(CY_SRF_DISABLE)
extern const mtb_srf_memory_protection_s_t mtb_srf_memory_protection_s[];
extern const uint8_t mtb_srf_protection_range_s_count;
#endif /* defined (COMPONENT_SECURE_DEVICE) && defined(COMPONENT_MW_MTB_SRF) && !defined(CY_SRF_DISABLE) */

void init_cycfg_protection(void);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* CYCFG_PROTECTION_H */
