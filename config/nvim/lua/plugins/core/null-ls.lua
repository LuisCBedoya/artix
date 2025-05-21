require('mason-null-ls').setup({
	ensure_installed = {
		'stylua', -- lua formatter
		'prettier', -- js, css, html, etc
		'black', -- python formatter
	},
	automatic_installation = true,
})

local null_ls = require('null-ls')

local augroup = vim.api.nvim_create_augroup('LspFormatting', {})

null_ls.setup({
	sources = {
		null_ls.builtins.formatting.prettier.with({
			extra_args = {
				'--use-tabs',
				'--tab-width',
				'2',
				'--print-width',
				'120',
				'--jsx-single-quote',
				'--trailing-comma',
				'es5',
			},
			prefer_local = 'node_modules/.bin',
			filetypes = {
				'javascript',
				'javascriptreact',
				'typescript',
				'typescriptreact',
				'html',
				'css',
				'scss',
				'less',
				'json',
				'jsonc',
				'markdown',
				'markdown.mdx',
				'yaml',
				'toml',
				'graphql',
				'vue',
				'svelte',
				'handlebars',
			},
		}),

		null_ls.builtins.formatting.stylua.with({
			extra_args = {
				'--indent-type',
				'Spaces',
				'--indent-width',
				'2',
				'--column-width',
				'120',
				'--line-endings',
				'Unix',
				'--quote-style',
				'AutoPreferSingle',
				'--call-parentheses',
				'Always',
				'--collapse-simple-statement',
				'Never',
			},
			filetypes = { 'lua' },
		}),
	},

	on_attach = function(client, bufnr)
		if client.supports_method('textDocument/formatting') then
			vim.api.nvim_clear_autocmds({ group = augroup, buffer = bufnr })

			vim.api.nvim_create_autocmd('BufWritePre', {
				group = augroup,
				buffer = bufnr,
				callback = function()
					vim.lsp.buf.format({
						bufnr = bufnr,
						filter = function(c)
							return c.name == 'null-ls'
						end,
						async = false,
					})
				end,
			})
		end
	end,
})
