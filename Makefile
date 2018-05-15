ROOT =.
#include global.mk

$(info $(NEURO))
$(info $(PATH))

.DEFAULT_GOAL = steps
	
clean:
	$(MAKE) -C life_001/make_x86	      clean
	$(MAKE) -C life_002/make_mb7707       clean
	$(MAKE) -C life_002/make_mc5103       clean
	$(MAKE) -C life_002/make_mc7601       clean
	$(MAKE) -C life_002/make_x86		  clean
	$(MAKE) -C life_003/make_mb7707       clean
	$(MAKE) -C life_003/make_mc5103       clean
	$(MAKE) -C life_003/make_mc7601       clean
	$(MAKE) -C life_003/make_x86		  clean
	$(MAKE) -C life_004/make_mb7707       clean
	$(MAKE) -C life_004/make_mc5103       clean
	$(MAKE) -C life_004/make_mc7601       clean
	$(MAKE) -C life_004/make_mc12101_nmc1 clean
	$(MAKE) -C life_004/make_x86		  clean
	$(MAKE) -C life_005/make_mb7707       clean
	$(MAKE) -C life_005/make_mc5103       clean
	$(MAKE) -C life_005/make_mc7601       clean
	$(MAKE) -C life_005/make_mc12101_nmc1 clean
	$(MAKE) -C life_005/make_x86		  clean
	$(MAKE) -C life_006/make_mb7707       clean
	$(MAKE) -C life_006/make_mc5103       clean
	$(MAKE) -C life_006/make_mc7601       clean
	$(MAKE) -C life_006/make_mc12101_nmc1 clean
	$(MAKE) -C life_006/make_x86		  clean
	$(MAKE) -C life_007/make_mb7707       clean
	$(MAKE) -C life_007/make_mc5103       clean
	$(MAKE) -C life_007/make_mc7601       clean
	$(MAKE) -C life_007/make_mc12101_nmc1 clean
	$(MAKE) -C life_007/make_x86		  clean
	$(MAKE) -C life_008/make_mb7707       clean
	$(MAKE) -C life_008/make_mc5103       clean
	$(MAKE) -C life_008/make_mc7601       clean
	$(MAKE) -C life_008/make_mc12101_nmc1 clean
	$(MAKE) -C life_008/make_x86		  clean
	$(MAKE) -C life_009/make_mc7601       clean
	$(MAKE) -C life_009/make_x86		  clean
	$(MAKE) -C life_010/make_mc7601       clean
	$(MAKE) -C life_010/make_x86		  clean
	
kill: clean
	$(MAKE) -C life_001/make_x86	      kill
	$(MAKE) -C life_002/make_mb7707       kill
	$(MAKE) -C life_002/make_mc5103       kill
	$(MAKE) -C life_002/make_mc7601       kill
	$(MAKE) -C life_002/make_x86		  kill
	$(MAKE) -C life_003/make_mb7707       kill
	$(MAKE) -C life_003/make_mc5103       kill
	$(MAKE) -C life_003/make_mc7601       kill
	$(MAKE) -C life_003/make_x86		  kill
	$(MAKE) -C life_004/make_mb7707       kill
	$(MAKE) -C life_004/make_mc5103       kill
	$(MAKE) -C life_004/make_mc7601       kill
	$(MAKE) -C life_004/make_mc12101_nmc1 kill
	$(MAKE) -C life_004/make_x86		  kill
	$(MAKE) -C life_005/make_mb7707       kill
	$(MAKE) -C life_005/make_mc5103       kill
	$(MAKE) -C life_005/make_mc7601       kill
	$(MAKE) -C life_005/make_mc12101_nmc1 kill
	$(MAKE) -C life_005/make_x86		  kill
	$(MAKE) -C life_006/make_mb7707       kill
	$(MAKE) -C life_006/make_mc5103       kill
	$(MAKE) -C life_006/make_mc7601       kill
	$(MAKE) -C life_006/make_mc12101_nmc1 kill
	$(MAKE) -C life_006/make_x86		  kill
	$(MAKE) -C life_007/make_mb7707       kill
	$(MAKE) -C life_007/make_mc5103       kill
	$(MAKE) -C life_007/make_mc7601       kill
	$(MAKE) -C life_007/make_mc12101_nmc1 kill
	$(MAKE) -C life_007/make_x86		  kill
	$(MAKE) -C life_008/make_mb7707       kill
	$(MAKE) -C life_008/make_mc5103       kill
	$(MAKE) -C life_008/make_mc7601       kill
	$(MAKE) -C life_008/make_mc12101_nmc1 kill
	$(MAKE) -C life_008/make_x86		  kill
	$(MAKE) -C life_009/make_mc7601       kill
	$(MAKE) -C life_009/make_x86		  kill
	$(MAKE) -C life_010/make_mc7601       kill
	$(MAKE) -C life_010/make_x86		  kill
	
steps:
	$(MAKE) -C life_001/make_x86
	$(MAKE) -C life_002/make_mb7707
	$(MAKE) -C life_002/make_mc5103 
	$(MAKE) -C life_002/make_mc7601
	$(MAKE) -C life_002/make_x86
	$(MAKE) -C life_003/make_mb7707
	$(MAKE) -C life_003/make_mc5103
	$(MAKE) -C life_003/make_mc7601
	$(MAKE) -C life_003/make_x86
	$(MAKE) -C life_004/make_mb7707
	$(MAKE) -C life_004/make_mc5103
	$(MAKE) -C life_004/make_mc7601
	$(MAKE) -C life_004/make_mc12101_nmc1
	$(MAKE) -C life_004/make_x86
	$(MAKE) -C life_005/make_mb7707
	$(MAKE) -C life_005/make_mc5103
	$(MAKE) -C life_005/make_mc7601
	$(MAKE) -C life_005/make_mc12101_nmc1
	$(MAKE) -C life_005/make_x86
	$(MAKE) -C life_006/make_mb7707
	$(MAKE) -C life_006/make_mc5103
	$(MAKE) -C life_006/make_mc7601
	$(MAKE) -C life_006/make_mc12101_nmc1
	$(MAKE) -C life_006/make_x86
	$(MAKE) -C life_007/make_mb7707
	$(MAKE) -C life_007/make_mc5103
	$(MAKE) -C life_007/make_mc7601
	$(MAKE) -C life_007/make_mc12101_nmc1
	$(MAKE) -C life_007/make_x86
	$(MAKE) -C life_008/make_mb7707
	$(MAKE) -C life_008/make_mc5103
	$(MAKE) -C life_008/make_mc7601
	$(MAKE) -C life_008/make_mc12101_nmc1
	$(MAKE) -C life_008/make_x86
	$(MAKE) -C life_009/make_mc7601
	$(MAKE) -C life_009/make_x86
	$(MAKE) -C life_010/make_mc7601
	$(MAKE) -C life_010/make_x86
	
test:
	$(MAKE) -C life_001/make_x86	      run
	$(MAKE) -C life_002/make_mb7707       run
	$(MAKE) -C life_002/make_mc5103       run
	$(MAKE) -C life_002/make_mc7601       run
	$(MAKE) -C life_002/make_x86          run
	$(MAKE) -C life_003/make_mb7707       run
	$(MAKE) -C life_003/make_mc5103       run
	$(MAKE) -C life_003/make_mc7601       run
	$(MAKE) -C life_003/make_x86          run
	$(MAKE) -C life_004/make_mb7707       run
	$(MAKE) -C life_004/make_mc5103       run 
	$(MAKE) -C life_004/make_mc7601       run
	$(MAKE) -C life_004/make_mc12101_nmc1 run
	$(MAKE) -C life_004/make_x86          run
	$(MAKE) -C life_005/make_mb7707       run
	$(MAKE) -C life_005/make_mc5103       run 
	$(MAKE) -C life_005/make_mc7601       run 
	$(MAKE) -C life_005/make_mc12101_nmc1 run
	$(MAKE) -C life_005/make_x86          run
	$(MAKE) -C life_006/make_mb7707       run
	$(MAKE) -C life_006/make_mc5103       run 
	$(MAKE) -C life_006/make_mc7601       run 
	$(MAKE) -C life_006/make_mc12101_nmc1 run
	$(MAKE) -C life_006/make_x86          run
	$(MAKE) -C life_007/make_mb7707       run
	$(MAKE) -C life_007/make_mc5103       run 
	$(MAKE) -C life_007/make_mc7601       run 
	$(MAKE) -C life_007/make_mc12101_nmc1 run
	$(MAKE) -C life_007/make_x86          run
	$(MAKE) -C life_008/make_mb7707       run
	$(MAKE) -C life_008/make_mc5103       run 
	$(MAKE) -C life_008/make_mc7601       run
	$(MAKE) -C life_008/make_mc12101_nmc1 run
	$(MAKE) -C life_008/make_x86          run
	$(MAKE) -C life_009/make_mc7601       run
	$(MAKE) -C life_009/make_x86          run
	$(MAKE) -C life_010/make_mc7601       run	
	$(MAKE) -C life_010/make_x86          run
	