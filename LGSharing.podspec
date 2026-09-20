Pod::Spec.new do |s|
    s.name = 'LGSharing'
    s.version = '1.0.2'
    s.platform = :ios, '12.0'
    s.license = 'MIT'
    s.homepage = 'https://github.com/LGLibs/LGSharing'
    s.author = { 'Grigorii Lutkov' => 'grigorii@lutkov.dev' }
    s.source = { :git => 'https://github.com/LGLibs/LGSharing.git', :tag => s.version }
    s.summary = 'iOS helper for easy sharing with email, message or social networks like facebook, twitter, google+ and vkontakte'
    s.requires_arc = true
    s.source_files = 'LGSharing/*.{h,m}'
    s.source_files = 'LGSharing/**/*.{h,m}'
    s.dependency 'VK-ios-sdk', '~> 1.2.0'
    s.dependency 'google-plus-ios-sdk', '~> 1.7.0'
end
