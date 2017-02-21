cc = meson.get_compiler('c')
pthread_dep = cc.find_library('pthread', required : false)

executable('date_from_epoch', 'date_from_epoch.c')
executable('fisher_yates_shuffle', 'fisher_yates_shuffle.c')
executable('largest_contiguous', 'largest_contiguous.c')
executable('mapreduce_word_frequency', 'mapreduce_word_frequency.c',
  dependencies : pthread_dep)
executable('months_starting_on_weekday', 'months_starting_on_weekday.c')
executable('shuffle_cards', 'shuffle_cards.c')
executable('subsets', 'subsets.c')
executable('neighbour_areas', 'neighbour_areas.c')
executable('time_conversion', 'time_conversion.c')
