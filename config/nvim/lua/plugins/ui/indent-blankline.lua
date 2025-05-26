vim.api.nvim_set_hl(0, 'Whitespace', { fg = '#262626' }) -- gris tenue
vim.api.nvim_set_hl(0, 'CursorColumn', { bg = '#151515' }) -- fondo tenue para columna actual

local highlight = {
  'CursorColumn',
  'Whitespace',
}

require('ibl').setup({
  indent = {
    highlight = highlight,
    char = '',
  },
  whitespace = {
    highlight = highlight,
    remove_blankline_trail = false,
  },
  scope = { enabled = false },
})
