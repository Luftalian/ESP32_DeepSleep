init:
	git submodule add https://github.com/CREATE-ROCKET/Avi_ESP_Libs.git lib

branch-push:
	git checkout -b $(branch)
	git add .
	git commit -m "$(branch)"
	git push --set-upstream origin $(branch)

clear:
	rm -rf ./src/utils

delete-submodule:
	git submodule deinit -f lib
	git rm -f lib
	rm -rf .git/modules/lib

set-submodule:
	git submodule add https://github.com/CREATE-ROCKET/Avi_ESP_Libs.git lib

update-submodule:
	git submodule update --remote

obsolesce-submodule:
	git submodule update