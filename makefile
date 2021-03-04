.DEFAULT_GOAL := help

.PHONY: $(MAKECMDGOALS)

help:
ifeq ($(OS), Windows_NT)
	@powershell.exe -Command 'Write-Host -ForegroundColor Green "Possible targets :"; \
	Get-Content Makefile \
	| Select-String -Pattern "^[a-zA-Z_-]+:.*?##" \
	| %{[regex]::Match($$_, "(\w+):\s*##(.*)"); } \
	| %{ Write-Host -NoNewline -ForegroundColor Blue ("    {0,-35}" -f $$_.captures.groups[1].value); \
	Write-Host $$_.captures.groups[2].value; }'
else
	@echo "\033[32mPossible targets :"
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "    \033[36m%-30s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)
endif

all: ## Build and run locally and within docker
	build
	docker

build: ## Build and run locally
ifeq ($(OS), Windows_NT)
	@powershell.exe -Command 'Building on windows...'
else
ifeq ($(shell uname), Darwin)
	@mkdir -p ostl/out
	@cd ostl/out \
	&& cmake \
        -G "Unix Makefiles" \
        -DCMAKE_C_COMPILER=gcc \
        -DCMAKE_CXX_COMPILER=g++ \
		-DCMAKE_TOOLCHAIN_FILE=$(shell find /usr -name "vcpkg.cmake" 2>/dev/null) \
		-DVCPKG_TARGET_TRIPLET=x64-osx \
        .. \
    && make all VERBOSE=1
else
	@echo "Building on linux"
endif
endif


docker: ## Build and run all docker compilers
	docker-compose up --build
	docker-compose down

docker-gcc: ## Build and run gcc compilation
	docker build -f dockerfiles/compiler/Dockerfile --tag gcc:latest --build-arg CC=gcc-10 --build-arg CXX=g++-10 ./ostl
	docker run --name gcc gcc:latest
	docker rm --force gcc

docker-clang: ## Build and run clang compilation
	docker build -f dockerfiles/compiler/Dockerfile --tag clang:latest --build-arg CC=clang-11 --build-arg CXX=clang++-11 ./ostl
	docker run --name clang clang:latest
	docker rm --force clang

format: ## Format the code
ifeq ($(OS), Windows_NT)
	@powershell.exe -Command \
	"foreach ($$file in (Get-ChildItem -Path ostl/source,ostl/test,ostl/example -File -Include *.cpp,*.hpp,*.inl -Recurse)) \
	{ \
		clang-format -i -style=file $$file.FullName \
	}"
else
ifeq ($(shell uname), Darwin)
	@find -E ostl/source/ ostl/test/ ostl/example/ -regex ".*\.(hpp|cpp|inl)" | xargs clang-format -i -style=file
else
	@find ostl/source/ ostl/test/ ostl/example/ -regextype posix-egrep -regex ".*\.(hpp|cpp|inl)" | xargs realpath | xargs clang-format -i -style=file
endif
endif

clean-all: ## Clean all output
	clean-docker
	clean

clean-docker: ## Clean docker's output directory
	@rm -rf out

clean: ## Clean the local output directory
	@rm -rf ostl/out
