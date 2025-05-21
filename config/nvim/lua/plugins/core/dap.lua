local M = {}

function M.setup()
  local dap = require('dap')
  local mason_dap = require('mason-nvim-dap')

  mason_dap.setup({
    ensure_installed = { 'python', 'bash' }, -- nombres correctos
    automatic_installation = true, -- activa instalación automática
    handlers = {
      function(config)
        -- fallback handler para adaptadores sin config específica
        mason_dap.default_setup(config)
      end,

      python = function(config)
        config.adapters = {
          type = 'executable',
          command = 'python',
          args = { '-m', 'debugpy.adapter' },
        }
        mason_dap.default_setup(config)
      end,
    },
  })

  -- opcional si ya tienes handler de python, pero puedes dejarlo para asegurarte
  dap.configurations.python = {
    {
      type = 'python',
      request = 'launch',
      name = 'Launch file',
      program = '${file}',
      pythonPath = function()
        local cwd = vim.fn.getcwd()
        local paths = {
          cwd .. '/venv/bin/python',
          cwd .. '/.venv/bin/python',
          '/usr/bin/python3',
          'python',
        }
        for _, path in ipairs(paths) do
          if vim.fn.executable(path) == 1 then
            return path
          end
        end
      end,
    },
  }
end

return M
