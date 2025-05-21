local autocmd = vim.api.nvim_create_autocmd
local alacrittyAutoGroup = vim.api.nvim_create_augroup('alacritty', { clear = true })

autocmd('FileType', {
  pattern = 'qf',
  callback = function()
    vim.opt_local.buflisted = false
  end,
})

autocmd({ 'UIEnter', 'BufReadPost', 'BufNewFile' }, {
  group = vim.api.nvim_create_augroup('NvFilePost', { clear = true }),
  callback = function(args)
    local file = vim.api.nvim_buf_get_name(args.buf)
    local buftype = vim.api.nvim_get_option_value('buftype', { buf = args.buf })

    if not vim.g.ui_entered and args.event == 'UIEnter' then
      vim.g.ui_entered = true
    end

    if file ~= '' and buftype ~= 'nofile' and vim.g.ui_entered then
      vim.api.nvim_exec_autocmds('User', { pattern = 'FilePost', modeline = false })
      vim.api.nvim_del_augroup_by_name('NvFilePost')

      vim.schedule(function()
        vim.api.nvim_exec_autocmds('FileType', {})

        if vim.g.editorconfig then
          require('editorconfig').config(args.buf)
        end
      end)
    end
  end,
})

-- ############################################ alacritty
vim.api.nvim_create_autocmd('VimEnter', {
  group = alacrittyAutoGroup,
  callback = function()
    vim.fn.system(
      "alacritty msg --socket $ALACRITTY_SOCKET config -w $ALACRITTY_WINDOW_ID options 'window.padding.x=0' 'window.padding.y=0' 'window.dynamic_padding=false'"
    )
  end,
})

vim.api.nvim_create_autocmd('VimLeavePre', {
  group = alacrittyAutoGroup,
  callback = function()
    vim.fn.jobstart('alacritty msg --socket $ALACRITTY_SOCKET config -w $ALACRITTY_WINDOW_ID -r', { detach = true })
  end,
})

-- ############################################### lazy check
vim.api.nvim_create_autocmd('VimEnter', {
  callback = function()
    vim.defer_fn(function()
      require('lazy').check({ show = false })
    end, 100) -- delay en milisegundos
  end,
})
