# setting the chosen locale
if(LOCALE MATCHES "^es[_-]")
  set(STUMPLESS_LANGUAGE "es-ES")
  set(USE_LOCALE_ES_ES TRUE)
elseif(LOCALE MATCHES "^fr[_-]")
  set(STUMPLESS_LANGUAGE "fr-FR")
  set(USE_LOCALE_FR_FR TRUE)
elseif(LOCALE MATCHES "^de[_-]")
  set(STUMPLESS_LANGUAGE "de-DE")
  set(USE_LOCALE_DE_DE TRUE)
elseif(LOCALE MATCHES "^it[_-]")
  set(STUMPLESS_LANGUAGE "it-IT")
  set(USE_LOCALE_IT_IT TRUE)
elseif(LOCALE MATCHES "^sv[_-]")
  set(STUMPLESS_LANGUAGE "sv-SE")
  set(USE_LOCALE_SV_SE TRUE)
elseif(LOCALE MATCHES "^sk[_-]")
  set(STUMPLESS_LANGUAGE "sk-SK")
  set(USE_LOCALE_SK_SK TRUE)
elseif(LOCALE MATCHES "^bg[_-]")
  set(STUMPLESS_LANGUAGE "bg-BG")
  set(USE_LOCALE_BG_BG TRUE)
elseif(LOCALE MATCHES "^cz[_-]")
  set(STUMPLESS_LANGUAGE "cz-CZ")
  set(USE_LOCALE_CZ_CZ TRUE)
elseif(LOCALE MATCHES "^pl[_-]")
  set(STUMPLESS_LANGUAGE "pl-PL")
  set(USE_LOCALE_PL_PL TRUE)
elseif(LOCALE MATCHES "^sw[_-]")
  set(STUMPLESS_LANGUAGE "sw-KE")
  set(USE_LOCALE_SW_KE TRUE)
elseif(LOCALE MATCHES "^el[_-]")
  set(STUMPLESS_LANGUAGE "el-GR")
  set(USE_LOCALE_EL_GR TRUE)
elseif(LOCALE MATCHES "^pt[_-]")
  set(STUMPLESS_LANGUAGE "pt-BR")
  set(USE_LOCALE_PT_BR TRUE)
elseif(LOCALE MATCHES "^zh[_-]")
  set(STUMPLESS_LANGUAGE "zh-CN")
  set(USE_LOCALE_ZH_CN TRUE)
elseif(LOCALE MATCHES "^hi[_-]")
  set(STUMPLESS_LANGUAGE "hi-IN")
  set(USE_LOCALE_HI_IN TRUE)
elseif(LOCALE MATCHES "^bn[_-]")
  set(STUMPLESS_LANGUAGE "bn-IN")
  set(USE_LOCALE_BN_IN TRUE)
elseif(LOCALE MATCHES "^te[_-]")
  set(STUMPLESS_LANGUAGE "te-IN")
  set(USE_LOCALE_TE_IN TRUE)
elseif(LOCALE MATCHES "^da[_-]")
  set(STUMPLESS_LANGUAGE "da-DK")
  set(USE_LOCALE_DA_DK TRUE)
elseif(LOCALE MATCHES "^he[_-]")
  set(STUMPLESS_LANGUAGE "he-IL")
  set(USE_LOCALE_HE_IL TRUE)
elseif(LOCALE MATCHES "^tr[_-]")
  set(STUMPLESS_LANGUAGE "tr-TR")
  set(USE_LOCALE_TR_TR TRUE)
elseif(LOCALE MATCHES "^hu[_-]")
  set(STUMPLESS_LANGUAGE "hu-HU")
  set(USE_LOCALE_HU_HU TRUE)
elseif(LOCALE MATCHES "^sq[_-]")
  set(STUMPLESS_LANGUAGE "sq-AL")
  set(USE_LOCALE_SQ_AL TRUE)
elseif(LOCALE MATCHES "^si[_-]")
  set(STUMPLESS_LANGUAGE "si-LK")
  set(USE_LOCALE_SI_LK TRUE)
elseif(LOCALE MATCHES "^ja[_-]")
  set(STUMPLESS_LANGUAGE "ja-JP")
  set(USE_LOCALE_JA_JP TRUE)
else()
  if(NOT LOCALE MATCHES "^en[_-]")
    message("building default language en-US")
  endif()
  set(STUMPLESS_LANGUAGE "en-US")
  set(USE_LOCALE_EN_US TRUE)
endif()


# set the input files for documentation
if(USE_LOCALE_ZH_CN)
  set(L10N_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/l10n/zh-cn/包含")
  set(L10N_EXAMPLE_DIR "${PROJECT_SOURCE_DIR}/l10n/zh-cn/文档/示例")
  set(DOXYGEN_OUTPUT_LANGUAGE "Chinese")
else() # default to USE_LOCALE_EN_US
  set(L10N_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/")
  set(L10N_EXAMPLE_DIR "${PROJECT_SOURCE_DIR}/docs/examples")
  set(DOXYGEN_OUTPUT_LANGUAGE "English")
endif()
