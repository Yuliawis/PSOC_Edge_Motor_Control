 



























#include "cycfg_protection.h"
#include "cycfg_system.h"

#if  (CY_SYSTEM_CPU_M33) && defined(COMPONENT_SECURE_DEVICE) && defined(CY_PDL_TZ_ENABLED)
#include "cycfg_ppc.h"
#include "ifx_se_platform.h"
#endif /*  (CY_SYSTEM_CPU_M33) && defined(COMPONENT_SECURE_DEVICE) && defined(CY_PDL_TZ_ENABLED) */

#if defined (COMPONENT_SECURE_DEVICE) && defined(COMPONENT_MW_MTB_SRF) && !defined(CY_SRF_DISABLE)
const mtb_srf_memory_protection_s_t mtb_srf_memory_protection_s[] =
{
    {
        .ranges = mxrramc_0_mpc_0_srf_protection_range_s,
        .size = 4U,
    },
    {
        .ranges = smif_0_mpc_0_srf_protection_range_s,
        .size = 6U,
    },
    {
        .ranges = socmem_0_mpc_0_srf_protection_range_s,
        .size = 2U,
    },
    {
        .ranges = mxsramc_0_mpc_0_srf_protection_range_s,
        .size = 3U,
    },
    {
        .ranges = mxsramc_1_mpc_0_srf_protection_range_s,
        .size = 2U,
    },
};
const uint8_t mtb_srf_protection_range_s_count = sizeof(mtb_srf_memory_protection_s) / sizeof(mtb_srf_memory_protection_s_t);
#endif /* defined (COMPONENT_SECURE_DEVICE) && defined(COMPONENT_MW_MTB_SRF) && !defined(CY_SRF_DISABLE) */

void init_cycfg_protection(void)
{
#if (CY_SYSTEM_CPU_M33) && defined(COMPONENT_SECURE_DEVICE) && !defined(CYBSP_SKIP_SAU_INIT)
    Cy_SAU_Init(SAU, SAU_config, sizeof(SAU_config) / sizeof(SAU_config[0]));
#endif /* (CY_SYSTEM_CPU_M33) && defined(COMPONENT_SECURE_DEVICE) && !defined(CYBSP_SKIP_SAU_INIT) */
#if  (CY_SYSTEM_CPU_M33) && defined(COMPONENT_SECURE_DEVICE) && defined(CY_PDL_TZ_ENABLED) && !defined(CYBSP_SKIP_MPC_INIT) && !defined(CY_DEVICE_FEATURE_MPC_LOCKED)
    init_cycfg_mpc();
#endif /*  (CY_SYSTEM_CPU_M33) && defined(COMPONENT_SECURE_DEVICE) && defined(CY_PDL_TZ_ENABLED) && !defined(CYBSP_SKIP_MPC_INIT) && !defined(CY_DEVICE_FEATURE_MPC_LOCKED) */
#if  (CY_SYSTEM_CPU_M33) && defined(COMPONENT_SECURE_DEVICE) && defined(CY_PDL_TZ_ENABLED) && !defined(CYCFG_PROTECTION_SE_ENABLE) && !defined(CYBSP_SKIP_PPC_INIT)
    ifx_se_disable(NULL);
#endif /*  (CY_SYSTEM_CPU_M33) && defined(COMPONENT_SECURE_DEVICE) && defined(CY_PDL_TZ_ENABLED) && !defined(CYCFG_PROTECTION_SE_ENABLE) && !defined(CYBSP_SKIP_PPC_INIT) */
#if (CY_SYSTEM_CPU_M33) && defined(COMPONENT_SECURE_DEVICE) && defined(CY_PDL_TZ_ENABLED) && !defined(CYBSP_SKIP_PPC_INIT)
    init_cycfg_ppc0();
    init_cycfg_ppc1();
#endif /* (CY_SYSTEM_CPU_M33) && defined(COMPONENT_SECURE_DEVICE) && defined(CY_PDL_TZ_ENABLED) && !defined(CYBSP_SKIP_PPC_INIT) */
#if (CY_SYSTEM_CPU_M55) && !defined(CYBSP_SKIP_MPU_INIT)
    Cy_MPU_Init(cycfg_mpu_cm55_ns_0_config, sizeof(cycfg_mpu_cm55_ns_0_config) / sizeof(cycfg_mpu_cm55_ns_0_config[0]));
#endif /* (CY_SYSTEM_CPU_M55) && !defined(CYBSP_SKIP_MPU_INIT) */
}
